// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/jump_on_tree

#include "../../library/tree/lca.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    LCA lca(g, 0);
    while (q--) {
        int s, t, i;
        cin >> s >> t >> i;
        cout << lca.jump(s, t, i) << "\n";
    }
}
