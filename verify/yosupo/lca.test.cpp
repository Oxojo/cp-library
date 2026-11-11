// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/lca

#include "../../library/tree/lca.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        g[p].push_back(i);
        g[i].push_back(p);
    }
    LCA lca(g, 0);
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca.lca(u, v) << "\n";
    }
}
