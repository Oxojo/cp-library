// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/tree_diameter

#include "../../library/tree/tree_diameter.hpp"

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    Graph<ll> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        g.add(a, b, c);
    }
    WeightedTreeDiameter<ll> dia(g);
    cout << dia.len << " " << dia.path.size() << "\n";
    for (int i = 0; i < (int)dia.path.size(); i++) {
        cout << dia.path[i] << " \n"[i + 1 == (int)dia.path.size()];
    }
}
