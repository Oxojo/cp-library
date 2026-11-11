// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/vertex_add_path_sum

#include "../../library/structure/FenwickTree.hpp"
#include "../../library/tree/hld.hpp"

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (auto& x : a) cin >> x;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    HLD hld(g, 0);
    FenwickTree<ll> bit(n);
    for (int v = 0; v < n; v++) bit.apply(hld.in[v], a[v]);

    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int p;
            ll x;
            cin >> p >> x;
            bit.apply(hld.in[p], x);
        } else {
            int u, v;
            cin >> u >> v;
            ll sum = 0;
            for (auto [l, r] : hld.path_ranges(u, v)) sum += bit.prod(l, r - 1);
            cout << sum << "\n";
        }
    }
}
