// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_B

#include "../../library/graph/dinic.hpp"

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Dinic<ll> mf(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        mf.add_edge(u, v, c);
    }
    int s, t;
    cin >> s >> t;
    cout << mf.max_flow(s, t) << "\n";
}
