// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/number_of_subsequences

#include "../../library/math/modint.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    map<long long, mint> dp;
    mint sum = 1;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        mint pre = dp[a];
        dp[a] = sum;
        sum += sum - pre;
    }
    cout << sum - 1 << "\n";
}
