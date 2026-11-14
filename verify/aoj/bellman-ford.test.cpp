// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B

#include "../../library/graph/bellman_ford.hpp"

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, r;
    cin >> n >> m >> r;
    Edges<ll> edges;
    for (int i = 0; i < m; i++) {
        int s, t;
        ll d;
        cin >> s >> t >> d;
        edges.emplace_back(s, t, d);
    }

    auto res = bellman_ford<ll>(n, edges, r);
    if (res.negative_cycle) {
        cout << "NEGATIVE CYCLE\n";
        return 0;
    }
    const ll INF = numeric_limits<ll>::max() / 4;
    for (int v = 0; v < n; v++) {
        if (res.dist[v] == INF)
            cout << "INF\n";
        else
            cout << res.dist[v] << "\n";
    }
}
