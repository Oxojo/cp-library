// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod

#include "../../library/math/combination.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    ll m;
    cin >> t >> m;
    int lim = (int)min<ll>(m - 1, 10000000);
    Combination comb(lim, m);
    while (t--) {
        int n, k;
        cin >> n >> k;
        cout << comb.C(n, k) << "\n";
    }
}
