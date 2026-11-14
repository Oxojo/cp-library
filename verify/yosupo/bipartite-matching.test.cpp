// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/bipartitematching

#include "../../library/graph/bipartite_matching.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int L, R, M;
    cin >> L >> R >> M;
    BipartiteMatching bm(L, R);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        bm.add_edge(a, b);
    }

    cout << bm.max_matching() << "\n";
    for (int u = 0; u < L; u++) {
        if (bm.match_left[u] != -1) cout << u << " " << bm.match_left[u] << "\n";
    }
}
