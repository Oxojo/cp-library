#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "template.hpp"
#include "modula.hpp"
#include "fps.hpp"
void solve() {
    ll n, m; cin >> n >> m;
    FPS<ll> a(n), b(m);
    cin >> a; cin >> b;
    auto c = a * b;
    cout << c << endl;
}
int main() {
    ll T = 1;
    // cin >> T;
    while (T--) solve();
}