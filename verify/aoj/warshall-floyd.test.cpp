// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_C

#include "../../library/graph/warshall_floyd.hpp"

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    const ll INF = numeric_limits<ll>::max() / 4;
    vector<vector<ll>> d(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++) d[i][i] = 0;
    for (int i = 0; i < m; i++) {
        int s, t;
        ll c;
        cin >> s >> t >> c;
        d[s][t] = min(d[s][t], c);
    }

    if (!warshall_floyd(d)) {
        cout << "NEGATIVE CYCLE\n";
        return 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j) cout << " ";
            if (d[i][j] == INF)
                cout << "INF";
            else
                cout << d[i][j];
        }
        cout << "\n";
    }
}
