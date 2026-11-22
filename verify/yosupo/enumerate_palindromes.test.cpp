// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/enumerate_palindromes

#include "../../library/string/manacher.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    auto l = manacher(s);
    for (int i = 0; i < (int)l.size(); ++i)
        cout << l[i] << " \n"[i + 1 == (int)l.size()];
}
