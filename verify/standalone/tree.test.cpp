// competitive-verifier: STANDALONE

#include "../../library/tree/lca.hpp"
#include "../../library/tree/tree_centroid.hpp"
#include "../../library/tree/tree_diameter.hpp"

#include <random>

#define CHECK(x)                                                          \
    do {                                                                  \
        if (!(x)) {                                                       \
            cerr << "FAILED: " #x << " (line " << __LINE__ << ")" << endl; \
            return 1;                                                     \
        }                                                                 \
    } while (0)

using ll = long long;

int main() {
    std::mt19937 rng(12345);

    // n = 1
    {
        vector<vector<int>> g(1);
        RootedTree tr(g, 0);
        LCA lca(g, 0);
        TreeCentroid tc(g);
        TreeDiameter dia(g);
        CHECK(tr.parent[0] == -1 && tr.depth[0] == 0 && tr.size[0] == 1);
        CHECK(lca.lca(0, 0) == 0 && lca.dist(0, 0) == 0);
        CHECK(tc.centroids.size() == 1 && tc.centroids[0] == 0);
        CHECK(dia.len == 0 && dia.path.size() == 1);

        Graph<ll> wg(1);
        WeightedTreeDiameter<ll> wdia(wg);
        CHECK(wdia.len == 0 && wdia.path.size() == 1);
    }

    for (int iter = 0; iter < 40; iter++) {
        int n = 2 + (int)(rng() % 18);
        vector<vector<int>> g(n);
        vector<pair<int, int>> edges;
        for (int v = 1; v < n; v++) {
            int p = (int)(rng() % v);
            g[p].push_back(v);
            g[v].push_back(p);
            edges.push_back({p, v});
        }

        // brute-force parent / depth from root 0
        vector<int> bp(n, -1), bd(n, 0);
        {
            vector<int> que{0};
            bp[0] = 0;
            for (size_t i = 0; i < que.size(); i++) {
                int v = que[i];
                for (int u : g[v]) {
                    if (bp[u] != -1) continue;
                    bp[u] = v;
                    bd[u] = bd[v] + 1;
                    que.push_back(u);
                }
            }
        }

        // --- RootedTree ---
        RootedTree tr(g, 0);
        CHECK(tr.parent[0] == -1);
        for (int v = 0; v < n; v++) {
            CHECK(tr.depth[v] == bd[v]);
            if (v) CHECK(tr.parent[v] == bp[v]);
            CHECK(tr.out[v] - tr.in[v] == tr.size[v]);
            for (int i = tr.in[v]; i < tr.out[v]; i++) CHECK(tr.is_ancestor(v, tr.order[i]));
            int cnt = 0;
            for (int u = 0; u < n; u++) cnt += tr.is_ancestor(v, u);
            CHECK(cnt == tr.size[v]);
        }

        // RootedTree also works with Graph<ll> (weights ignored)
        Graph<ll> wg1(n);
        for (auto [a, b] : edges) wg1.add(a, b, 1);
        RootedTree tr2(wg1, 0);
        CHECK(tr2.depth == tr.depth);
        CHECK(tr2.size == tr.size);

        // --- LCA ---
        LCA lca(g, 0);
        auto brute_lca = [&](int u, int v) {
            while (bd[u] > bd[v]) u = bp[u];
            while (bd[v] > bd[u]) v = bp[v];
            while (u != v) {
                u = bp[u];
                v = bp[v];
            }
            return u;
        };
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                int w = brute_lca(u, v);
                int d = bd[u] + bd[v] - 2 * bd[w];
                CHECK(lca.lca(u, v) == w);
                CHECK(lca.dist(u, v) == d);
                CHECK(lca.jump(u, v, -1) == -1);
                CHECK(lca.jump(u, v, d + 1) == -1);

                auto p = lca.path(u, v);
                CHECK((int)p.size() == d + 1);
                CHECK(p.front() == u && p.back() == v);
                for (size_t i = 0; i + 1 < p.size(); i++) {
                    bool connected = false;
                    for (int z : g[p[i]]) connected |= (z == p[i + 1]);
                    CHECK(connected);
                }
                for (int k = 0; k <= d; k++) CHECK(lca.jump(u, v, k) == p[k]);
            }
            for (int k = 0; k <= bd[u]; k++) {
                int x = u;
                for (int i = 0; i < k; i++) x = bp[x];
                CHECK(lca.kth_ancestor(u, k) == x);
            }
            CHECK(lca.kth_ancestor(u, bd[u] + 1) == -1);
        }

        // --- TreeCentroid ---
        vector<int> brute_centroids;
        for (int v = 0; v < n; v++) {
            vector<char> used(n, 0);
            used[v] = 1;
            int mx = 0;
            for (int s = 0; s < n; s++) {
                if (used[s]) continue;
                int c = 0;
                vector<int> st{s};
                used[s] = 1;
                while (!st.empty()) {
                    int a = st.back();
                    st.pop_back();
                    c++;
                    for (int b : g[a]) {
                        if (used[b]) continue;
                        used[b] = 1;
                        st.push_back(b);
                    }
                }
                mx = max(mx, c);
            }
            if (mx * 2 <= n) brute_centroids.push_back(v);
        }
        TreeCentroid tc(g);
        vector<int> got = tc.centroids;
        sort(got.begin(), got.end());
        CHECK(got == brute_centroids);

        // --- TreeDiameter (unweighted) ---
        int best = 0;
        for (int s = 0; s < n; s++) {
            vector<int> d(n, -1);
            vector<int> st{s};
            d[s] = 0;
            while (!st.empty()) {
                int v = st.back();
                st.pop_back();
                best = max(best, d[v]);
                for (int u : g[v]) {
                    if (d[u] != -1) continue;
                    d[u] = d[v] + 1;
                    st.push_back(u);
                }
            }
        }
        TreeDiameter dia(g);
        CHECK(dia.len == best);
        CHECK((int)dia.path.size() == dia.len + 1);
        CHECK(dia.path.front() == dia.s && dia.path.back() == dia.t);
        for (size_t i = 0; i + 1 < dia.path.size(); i++) {
            bool connected = false;
            for (int z : g[dia.path[i]]) connected |= (z == dia.path[i + 1]);
            CHECK(connected);
        }

        // --- WeightedTreeDiameter ---
        Graph<ll> wg(n);
        for (auto [a, b] : edges) {
            ll c = 1 + (ll)(rng() % 10);
            wg.add(a, b, c);
        }
        ll wbest = 0;
        for (int s = 0; s < n; s++) {
            vector<ll> d(n, -1);
            vector<int> st{s};
            d[s] = 0;
            while (!st.empty()) {
                int v = st.back();
                st.pop_back();
                wbest = max(wbest, d[v]);
                for (const auto& e : wg[v]) {
                    if (d[e.to] != -1) continue;
                    d[e.to] = d[v] + e.cost;
                    st.push_back(e.to);
                }
            }
        }
        WeightedTreeDiameter<ll> wdia(wg);
        CHECK(wdia.len == wbest);
        ll sum = 0;
        for (size_t i = 0; i + 1 < wdia.path.size(); i++) {
            ll c = -1;
            for (const auto& e : wg[wdia.path[i]]) {
                if (e.to == wdia.path[i + 1]) c = e.cost;
            }
            CHECK(c >= 0);
            sum += c;
        }
        CHECK(sum == wdia.len);
        CHECK(wdia.path.front() == wdia.s && wdia.path.back() == wdia.t);
    }

    return 0;
}
