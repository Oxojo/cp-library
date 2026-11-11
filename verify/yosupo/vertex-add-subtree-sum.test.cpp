// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/vertex_add_subtree_sum

#include "../../library/structure/FenwickTree.hpp"
#include "../../library/tree/rooted_tree.hpp"

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (auto& x : a) cin >> x;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        g[p].push_back(i);
        g[i].push_back(p);
    }

    RootedTree tr(g, 0);
    FenwickTree<ll> bit(n);
    for (int v = 0; v < n; v++) bit.apply(tr.in[v], a[v]);

    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int u;
            ll x;
            cin >> u >> x;
            bit.apply(tr.in[u], x);
        } else {
            int u;
            cin >> u;
            cout << bit.prod(tr.in[u], tr.out[u] - 1) << "\n";
        }
    }
}
