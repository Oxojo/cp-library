// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/shortest_path

#include "../../library/template/template.hpp"
#include "../../library/graph/graph.hpp"
#include "../../library/graph/dijkstra_restore.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    int s, t; cin >> s >> t;
    const long long inf = numeric_limits<long long>::max() / 4;
    Graph<long long> g(n);
    g.read(m, 0, 1, 1);
    auto dist = dijkstra_restore<long long>(g, s);
    if (dist[t].first == inf) {
        cout << -1 << "\n";
    } else {
        long long d = dist[t].first;
        vector<int> path;
        for (int v = t; v != -1; v = dist[v].second) {
            path.emplace_back(v);
        }
        reverse(begin(path), end(path));
        cout << d << ' ' << (int)path.size() - 1 << "\n";
        for (int i = 0; i < path.size() - 1; i++) {
            cout << path[i] << ' ' << path[i + 1] << "\n";
        }
    }
}
