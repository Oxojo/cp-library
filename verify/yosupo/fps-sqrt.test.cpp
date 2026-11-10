// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sqrt_of_formal_power_series
// competitive-verifier: TLE 30

#include "../../library/fps/fps.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    FPS<ll> a(n);
    for (auto& x : a) cin >> x;
    auto r = a.sqrt(n);
    if (r.empty()) {
        cout << -1 << "\n";
        return 0;
    }
    for (int i = 0; i < n; i++) cout << r[i] << " \n"[i + 1 == n];
}
