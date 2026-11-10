// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/pow_of_formal_power_series
// competitive-verifier: TLE 30

#include "../../library/fps/fps.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    ll k;
    cin >> n >> k;
    FPS<ll> a(n);
    for (auto& x : a) cin >> x;
    auto r = a.pow(k, n);
    for (int i = 0; i < n; i++) cout << r[i] << " \n"[i + 1 == n];
}
