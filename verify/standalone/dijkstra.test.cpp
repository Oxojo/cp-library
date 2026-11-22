// competitive-verifier: STANDALONE

#include "../../library/graph/dijkstra.hpp"
#include "../../library/graph/dijkstra_restore.hpp"

#include <random>

#define CHECK(x)                                                          \
    do {                                                                  \
        if (!(x)) {                                                       \
            cerr << "FAILED: " #x << " (line " << __LINE__ << ")" << endl; \
            return 1;                                                     \
        }                                                                 \
    } while (0)

int main() {
    using ll = long long;
    const ll INF = numeric_limits<ll>::max() / 4;

    mt19937_64 rng(20261123);
    for (int tc = 0; tc < 200; ++tc) {
        int n = 1 + (int)(rng() % 12);
        Graph<ll> g(n);
        vector<vector<ll>> d(n, vector<ll>(n, INF));
        for (int i = 0; i < n; ++i) d[i][i] = 0;

        int m = (int)(rng() % (n * n + 1));
        for (int i = 0; i < m; ++i) {
            int u = (int)(rng() % n);
            int v = (int)(rng() % n);
            ll w = (ll)(rng() % 1000000000ULL);
            g.add(u, v, w, true);
            d[u][v] = min(d[u][v], w);
        }

        // Floyd-Warshall as an independent reference.
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i) {
                if (d[i][k] == INF) continue;
                for (int j = 0; j < n; ++j) {
                    if (d[k][j] == INF) continue;
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }

        for (int s = 0; s < n; ++s) {
            auto dist = dijkstra<ll>(g, s);
            CHECK(dist == d[s]);

            auto dist_restore = dijkstra_restore<ll>(g, s);
            for (int v = 0; v < n; ++v)
                CHECK(dist_restore[v].first == d[s][v]);
        }
    }

    // Saturation: a huge edge cost must not overflow.
    {
        Graph<ll> g(2);
        g.add(0, 1, INF / 2, true);
        auto dist = dijkstra<ll>(g, 0);
        CHECK(dist[0] == 0);
        CHECK(dist[1] == INF / 2);
    }
    {
        Graph<ll> g(3);
        g.add(0, 1, INF / 2 + 1, true);
        g.add(1, 2, INF / 2 + 1, true);
        auto dist = dijkstra<ll>(g, 0);
        CHECK(dist[2] == INF);
    }

    cout << "OK" << endl;
    return 0;
}
