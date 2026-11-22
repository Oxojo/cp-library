// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/number_of_substrings

#include "../../library/string/suffix_array.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    auto sa = suffix_array(s);
    auto lcp = lcp_array(s, sa);
    long long n = (long long)s.size();
    long long ans = n * (n + 1) / 2;
    for (int x : lcp) ans -= x;
    cout << ans << "\n";
}
