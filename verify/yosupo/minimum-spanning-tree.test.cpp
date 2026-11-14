// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/minimum_spanning_tree

#include "../../library/graph/mst.hpp"

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Edges<ll> edges;
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        edges.emplace_back(a, b, c);
    }

    auto res = kruskal(n, edges);
    cout << res.cost << "\n";
    for (int i = 0; i < (int)res.edges.size(); i++) {
        cout << res.edges[i] << " \n"[i + 1 == (int)res.edges.size()];
    }
}
