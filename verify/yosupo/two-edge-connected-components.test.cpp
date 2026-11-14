// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/two_edge_connected_components

#include "../../library/graph/lowlink.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Lowlink low(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        low.add_edge(a, b);
    }
    low.build();

    int k = low.two_edge_component_count;
    vector<vector<int>> groups(k);
    for (int v = 0; v < n; v++) groups[low.two_edge_component[v]].push_back(v);

    cout << k << "\n";
    for (auto& gr : groups) {
        cout << gr.size();
        for (int v : gr) cout << " " << v;
        cout << "\n";
    }
}
