// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/discrete_logarithm_mod

#include "../../library/math/modula.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        ll x, y, m;
        cin >> x >> y >> m;
        cout << modlog<ll>(x, y, m) << "\n";
    }
}
