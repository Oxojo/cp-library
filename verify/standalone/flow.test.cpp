// competitive-verifier: STANDALONE

#include "../../library/graph/bipartite_matching.hpp"
#include "../../library/graph/dinic.hpp"

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

int main() {
    std::mt19937 rng(4242);

    // ---------- Dinic vs brute-force min cut ----------
    for (int iter = 0; iter < 80; iter++) {
        int n = 2 + (int)(rng() % 5);
        int m = (int)(rng() % 12);
        int s = 0, t = n - 1;

        vector<tuple<int, int, ll>> es;
        Dinic<ll> mf(n);
        for (int i = 0; i < m; i++) {
            int u = (int)(rng() % n), v = (int)(rng() % n);
            ll c = (ll)(rng() % 6);
            es.emplace_back(u, v, c);
            mf.add_edge(u, v, c);
        }

        ll best = BIG;
        for (int mask = 0; mask < (1 << n); mask++) {
            if (!((mask >> s) & 1)) continue;
            if ((mask >> t) & 1) continue;
            ll cut = 0;
            for (auto [u, v, c] : es)
                if (((mask >> u) & 1) && !((mask >> v) & 1)) cut += c;
            best = min(best, cut);
        }

        ll flow = mf.max_flow(s, t);
        CHECK(flow == best);

        auto side = mf.min_cut(s);
        ll cut = 0;
        for (auto [u, v, c] : es)
            if (side[u] && !side[v]) cut += c;
        CHECK(cut == flow);
        CHECK(side[s] && !side[t]);
    }

    // ---------- Bipartite matching vs brute force ----------
    for (int iter = 0; iter < 100; iter++) {
        int L = 1 + (int)(rng() % 5), R = 1 + (int)(rng() % 5);
        vector<vector<int>> g(L);
        for (int u = 0; u < L; u++) {
            for (int v = 0; v < R; v++)
                if (rng() % 3 == 0) g[u].push_back(v);
        }

        BipartiteMatching bm(L, R);
        for (int u = 0; u < L; u++)
            for (int v : g[u]) bm.add_edge(u, v);
        int got = bm.max_matching();

        vector<char> used(R, 0);
        int best = 0;
        function<void(int, int)> rec = [&](int u, int cnt) {
            if (u == L) {
                best = max(best, cnt);
                return;
            }
            rec(u + 1, cnt);
            for (int v : g[u]) {
                if (used[v]) continue;
                used[v] = 1;
                rec(u + 1, cnt + 1);
                used[v] = 0;
            }
        };
        rec(0, 0);
        CHECK(got == best);

        vector<char> usedR(R, 0);
        int cnt = 0;
        for (int u = 0; u < L; u++) {
            if (bm.match_left[u] == -1) continue;
            int v = bm.match_left[u];
            CHECK(0 <= v && v < R);
            CHECK(!usedR[v]);
            usedR[v] = 1;
            cnt++;
            CHECK(bm.match_right[v] == u);
            bool found = false;
            for (int z : g[u]) found |= (z == v);
            CHECK(found);
        }
        CHECK(cnt == got);
    }

    return 0;
}
