// competitive-verifier: STANDALONE

#include "../../library/graph/bfs.hpp"
#include "../../library/graph/bellman_ford.hpp"
#include "../../library/graph/lowlink.hpp"
#include "../../library/graph/mst.hpp"
#include "../../library/graph/scc.hpp"
#include "../../library/graph/topological_sort.hpp"
#include "../../library/graph/two_sat.hpp"
#include "../../library/graph/warshall_floyd.hpp"

#include <random>

#define CHECK(x)                                                          \
    do {                                                                  \
        if (!(x)) {                                                       \
            cerr << "FAILED: " #x << " (line " << __LINE__ << ")" << endl; \
            return 1;                                                     \
        }                                                                 \
    } while (0)

using ll = long long;
constexpr ll BIG = (1LL << 60);

namespace {
int comps_without(const vector<pair<int, int>>& edges, int n, int ban) {
    vector<vector<int>> g(n);
    for (auto [u, v] : edges) {
        if (u == ban || v == ban) continue;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<char> vis(n, 0);
    for (int v = 0; v < n; v++)
        if (v == ban) vis[v] = 1;
    int cnt = 0;
    for (int s = 0; s < n; s++) {
        if (vis[s]) continue;
        cnt++;
        vector<int> st{s};
        vis[s] = 1;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            for (int u : g[v]) {
                if (vis[u]) continue;
                vis[u] = 1;
                st.push_back(u);
            }
        }
    }
    return cnt;
}

bool connected_without_edge(const vector<pair<int, int>>& edges, int n, int ban, int a, int b) {
    if (a == b) return true;
    vector<vector<int>> g(n);
    for (int i = 0; i < (int)edges.size(); i++) {
        if (i == ban) continue;
        auto [u, v] = edges[i];
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<char> vis(n, 0);
    vector<int> st{a};
    vis[a] = 1;
    while (!st.empty()) {
        int v = st.back();
        st.pop_back();
        for (int u : g[v]) {
            if (vis[u]) continue;
            vis[u] = 1;
            st.push_back(u);
        }
    }
    return vis[b];
}
}  // namespace

int main() {
    std::mt19937 rng(2026);

    // ---------- SCC ----------
    for (int iter = 0; iter < 60; iter++) {
        int n = 1 + (int)(rng() % 8);
        int m = (int)(rng() % (n * n + 1));
        vector<vector<int>> g(n);
        vector<pair<int, int>> es;
        for (int i = 0; i < m; i++) {
            int u = (int)(rng() % n), v = (int)(rng() % n);
            g[u].push_back(v);
            es.push_back({u, v});
        }
        vector<vector<char>> reach(n, vector<char>(n, 0));
        for (auto [u, v] : es) reach[u][v] = 1;
        for (int i = 0; i < n; i++) reach[i][i] = 1;
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                if (reach[i][k])
                    for (int j = 0; j < n; j++)
                        if (reach[k][j]) reach[i][j] = 1;

        SCC scc(g);
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                CHECK(scc.same(u, v) == (reach[u][v] && reach[v][u]));
        for (auto [u, v] : es)
            if (scc.id[u] != scc.id[v]) CHECK(scc.id[u] < scc.id[v]);
        for (int c = 0; c < scc.size(); c++)
            for (int v : scc.groups[c]) CHECK(scc.id[v] == c);
    }

    // ---------- 2-SAT ----------
    for (int iter = 0; iter < 100; iter++) {
        int n = 1 + (int)(rng() % 5);
        int m = (int)(rng() % 7);
        vector<tuple<int, bool, int, bool>> cls;
        for (int i = 0; i < m; i++) {
            int a = (int)(rng() % n), b = (int)(rng() % n);
            bool f = rng() & 1, h = rng() & 1;
            cls.emplace_back(a, f, b, h);
        }

        bool brute = false;
        for (int mask = 0; mask < (1 << n) && !brute; mask++) {
            bool ok = true;
            for (auto [a, f, b, h] : cls) {
                bool va = ((mask >> a) & 1), vb = ((mask >> b) & 1);
                if (va != f && vb != h) ok = false;
            }
            if (ok) brute = true;
        }

        TwoSAT sat(n);
        for (auto [a, f, b, h] : cls) sat.add_clause(a, f, b, h);
        bool ok = sat.satisfiable();
        CHECK(ok == brute);
        if (ok) {
            for (auto [a, f, b, h] : cls)
                CHECK(sat.answer[a] == f || sat.answer[b] == h);
        }
    }

    // ---------- topological sort ----------
    for (int iter = 0; iter < 60; iter++) {
        int n = 1 + (int)(rng() % 8);
        vector<int> perm(n);
        iota(perm.begin(), perm.end(), 0);
        shuffle(perm.begin(), perm.end(), rng);
        vector<int> pos(n);
        for (int i = 0; i < n; i++) pos[perm[i]] = i;

        vector<vector<int>> g(n);
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (pos[u] < pos[v] && rng() % 3 == 0) g[u].push_back(v);
            }
        }
        auto ord = topological_sort(g);
        CHECK((int)ord.size() == n);
        vector<int> p2(n);
        for (int i = 0; i < n; i++) p2[ord[i]] = i;
        for (int u = 0; u < n; u++)
            for (int v : g[u]) CHECK(p2[u] < p2[v]);
    }
    for (int iter = 0; iter < 60; iter++) {
        int n = 1 + (int)(rng() % 7);
        vector<vector<int>> g(n);
        vector<vector<char>> r(n, vector<char>(n, 0));
        for (int i = 0; i < (int)(rng() % (n * n + 1)); i++) {
            int u = (int)(rng() % n), v = (int)(rng() % n);
            g[u].push_back(v);
            r[u][v] = 1;
        }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                if (r[i][k])
                    for (int j = 0; j < n; j++)
                        if (r[k][j]) r[i][j] = 1;
        bool cyc = false;
        for (int i = 0; i < n; i++) cyc |= r[i][i];
        CHECK(topological_sort(g).empty() == cyc);
    }

    // ---------- BFS ----------
    for (int iter = 0; iter < 60; iter++) {
        int n = 1 + (int)(rng() % 8);
        vector<vector<int>> g(n);
        vector<vector<ll>> d(n, vector<ll>(n, BIG));
        for (int i = 0; i < n; i++) d[i][i] = 0;
        for (int i = 0; i < (int)(rng() % (n * n + 1)); i++) {
            int u = (int)(rng() % n), v = (int)(rng() % n);
            g[u].push_back(v);
            d[u][v] = min(d[u][v], 1LL);
        }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (d[i][k] + d[k][j] < d[i][j]) d[i][j] = d[i][k] + d[k][j];
        int s = (int)(rng() % n);
        auto dist = bfs(g, s);
        for (int v = 0; v < n; v++)
            CHECK(dist[v] == (d[s][v] >= BIG ? -1 : (int)d[s][v]));
    }

    // ---------- 0-1 BFS ----------
    for (int iter = 0; iter < 60; iter++) {
        int n = 1 + (int)(rng() % 8);
        int m = (int)(rng() % 12);
        Graph<ll> g(n);
        for (int i = 0; i < m; i++) {
            int u = (int)(rng() % n), v = (int)(rng() % n);
            ll w = rng() % 2;
            g.add(u, v, w, true);
        }
        int s = (int)(rng() % n);
        auto dist = zero_one_bfs<ll>(g, s);

        vector<ll> d(n, BIG);
        vector<char> used(n, 0);
        d[s] = 0;
        for (int rep = 0; rep < n; rep++) {
            int v = -1;
            for (int i = 0; i < n; i++)
                if (!used[i] && (v == -1 || d[i] < d[v])) v = i;
            if (v == -1 || d[v] >= BIG) break;
            used[v] = 1;
            for (const auto& e : g[v]) d[e.to] = min(d[e.to], d[v] + e.cost);
        }
        for (int v = 0; v < n; v++) {
            if (d[v] >= BIG)
                CHECK(dist[v] == numeric_limits<ll>::max() / 4);
            else
                CHECK(dist[v] == d[v]);
        }
    }

    // ---------- Bellman-Ford ----------
    for (int iter = 0; iter < 60; iter++) {
        int n = 1 + (int)(rng() % 6);
        vector<vector<ll>> d(n, vector<ll>(n, BIG));
        for (int i = 0; i < n; i++) d[i][i] = 0;
        Edges<ll> edges;
        for (int i = 0; i < (int)(rng() % 10); i++) {
            int u = (int)(rng() % n), v = (int)(rng() % n);
            ll w = (ll)(rng() % 16) - 5;
            edges.emplace_back(u, v, w);
            d[u][v] = min(d[u][v], w);
        }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (d[i][k] < BIG && d[k][j] < BIG)
                        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        bool neg = false;
        for (int i = 0; i < n; i++) neg |= (d[i][i] < 0);

        int s = (int)(rng() % n);
        auto res = bellman_ford<ll>(n, edges, s);
        if (!neg) {
            CHECK(!res.negative_cycle);
            for (int v = 0; v < n; v++) {
                if (d[s][v] >= BIG)
                    CHECK(res.dist[v] == numeric_limits<ll>::max() / 4);
                else
                    CHECK(res.dist[v] == d[s][v]);
            }
        }
    }
    {
        // negative cycle reachable from s
        Edges<ll> edges;
        edges.emplace_back(0, 1, 1);
        edges.emplace_back(1, 0, -5);
        auto res = bellman_ford<ll>(2, edges, 0);
        CHECK(res.negative_cycle);

        // negative cycle not reachable from s
        Edges<ll> edges2;
        edges2.emplace_back(0, 1, 3);
        edges2.emplace_back(2, 3, 1);
        edges2.emplace_back(3, 2, -5);
        auto res2 = bellman_ford<ll>(4, edges2, 0);
        CHECK(!res2.negative_cycle);
        CHECK(res2.dist[1] == 3);
    }

    // ---------- Warshall-Floyd ----------
    {
        vector<vector<ll>> d(4, vector<ll>(4, BIG));
        for (int i = 0; i < 4; i++) d[i][i] = 0;
        d[0][1] = 2;
        d[1][2] = 3;
        d[0][2] = 10;
        d[2][3] = 1;
        CHECK(warshall_floyd(d, BIG));
        CHECK(d[0][2] == 5 && d[0][3] == 6);

        vector<vector<ll>> c(2, vector<ll>(2, BIG));
        for (int i = 0; i < 2; i++) c[i][i] = 0;
        c[0][1] = 1;
        c[1][0] = -3;
        CHECK(!warshall_floyd(c, BIG));
    }

    // ---------- Lowlink ----------
    for (int iter = 0; iter < 80; iter++) {
        int n = 1 + (int)(rng() % 7);
        int m = (int)(rng() % 11);
        vector<pair<int, int>> es;
        Lowlink low(n);
        for (int i = 0; i < m; i++) {
            int u = (int)(rng() % n), v = (int)(rng() % n);
            es.push_back({u, v});
            low.add_edge(u, v);
        }
        low.build();

        for (int eid = 0; eid < m; eid++) {
            auto [u, v] = es[eid];
            bool is_bridge = !connected_without_edge(es, n, eid, u, v);
            CHECK((bool)low.bridge[eid] == is_bridge);
        }

        int base = comps_without(es, n, -1);
        for (int v = 0; v < n; v++) {
            int after = comps_without(es, n, v);
            CHECK((bool)low.articulation[v] == (after > base));
        }

        // 2-edge-connected components: remove bridges and compare partition
        vector<vector<int>> g2(n);
        for (int eid = 0; eid < m; eid++) {
            if (low.bridge[eid]) continue;
            auto [u, v] = es[eid];
            g2[u].push_back(v);
            g2[v].push_back(u);
        }
        vector<int> cid(n, -1);
        int cc = 0;
        for (int s = 0; s < n; s++) {
            if (cid[s] != -1) continue;
            cid[s] = cc;
            vector<int> st{s};
            while (!st.empty()) {
                int v = st.back();
                st.pop_back();
                for (int u : g2[v]) {
                    if (cid[u] != -1) continue;
                    cid[u] = cc;
                    st.push_back(u);
                }
            }
            cc++;
        }
        CHECK(cc == low.two_edge_component_count);
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                CHECK((cid[u] == cid[v]) == (low.two_edge_component[u] == low.two_edge_component[v]));
    }

    // ---------- MST ----------
    for (int iter = 0; iter < 40; iter++) {
        int n = 2 + (int)(rng() % 5);
        Edges<ll> edges;
        for (int v = 1; v < n; v++) {
            int p = (int)(rng() % v);
            edges.emplace_back(p, v, (ll)(rng() % 21));
        }
        int extra = (int)(rng() % 5);
        for (int i = 0; i < extra; i++) {
            int u = (int)(rng() % n), v = (int)(rng() % n);
            edges.emplace_back(u, v, (ll)(rng() % 21));
        }
        int m = (int)edges.size();

        ll best = BIG;
        for (int mask = 0; mask < (1 << m); mask++) {
            if (__builtin_popcount((unsigned)mask) != n - 1) continue;
            UnionFind uf(n);
            ll cost = 0;
            bool ok = true;
            for (int i = 0; i < m; i++) {
                if (!((mask >> i) & 1)) continue;
                if (!uf.unite(edges[i].from, edges[i].to)) ok = false;
                cost += edges[i].cost;
            }
            if (ok) best = min(best, cost);
        }

        auto res = kruskal(n, edges);
        CHECK(res.cost == best);
        CHECK((int)res.edges.size() == n - 1);
        UnionFind uf(n);
        ll sum = 0;
        for (int id : res.edges) {
            CHECK(uf.unite(edges[id].from, edges[id].to));
            sum += edges[id].cost;
        }
        CHECK(sum == res.cost);
    }

    return 0;
}
