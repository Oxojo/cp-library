// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/scc

#include "../../library/graph/scc.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    SCC scc(g);
    cout << scc.size() << "\n";
    for (auto& gr : scc.groups) {
        cout << gr.size();
        for (int v : gr) cout << " " << v;
        cout << "\n";
    }
}
