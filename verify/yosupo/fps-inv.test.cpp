// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/inv_of_formal_power_series

#include "../../library/fps/fps.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    FPS<ll> a(n);
    for (auto& x : a) cin >> x;
    auto r = a.inv(n);
    for (int i = 0; i < n; i++) cout << r[i] << " \n"[i + 1 == n];
}
