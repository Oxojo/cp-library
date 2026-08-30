// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_A

#include "../../library/template/template.hpp"
#include "../../library/graph/graph.hpp"
#include "../../library/graph/dijkstra.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    int s; cin >> s;
    const long long inf = numeric_limits<long long>::max() / 4;
    Graph<long long> g(n);
    g.read(m, 0, 1, 1);
    vector<long long> dist = dijkstra<long long>(g, s);
    for (int i = 0; i < n; i++) {
        if (dist[i] == inf) {
            cout << "INF" << "\n";
        } else {
            cout << dist[i] << "\n";
        }
    }
}
