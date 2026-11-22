// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/eertree

#include "../../library/string/eertree.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    Eertree et;
    et.build(s);

    int n = et.size();
    cout << n << "\n";
    for (int v = 2; v < (int)et.len.size(); ++v) {
        int p = et.parent[v];
        int out_p = (p == 1 ? -1 : (p == 0 ? 0 : p - 1));
        int l = et.link[v];
        int out_l = (l == 0 ? 0 : l - 1);
        cout << out_p << " " << out_l << "\n";
    }
    for (int i = 0; i < (int)s.size(); ++i)
        cout << et.prefix_last[i] - 1 << " \n"[i + 1 == (int)s.size()];
}
