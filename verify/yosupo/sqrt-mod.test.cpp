// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sqrt_mod

#include "../../library/math/modula.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        ll y, p;
        cin >> y >> p;
        cout << modsqrt(y, p) << "\n";
    }
}
