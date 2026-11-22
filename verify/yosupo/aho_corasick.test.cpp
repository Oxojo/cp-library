// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/aho_corasick

#include "../../library/string/aho_corasick.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    AhoCorasick ac;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        ac.add(s);
    }
    ac.build();

    int m = (int)ac.nodes.size();
    cout << m << "\n";
    for (int v = 1; v < m; ++v)
        cout << ac.nodes[v].parent << " " << ac.nodes[v].link << "\n";
    for (int i = 0; i < n; ++i) cout << ac.ends[i] << " \n"[i + 1 == n];
}
