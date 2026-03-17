// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod

#include "../../library/template/template.hpp"
#include "../../library/math/modula.hpp"
#include "../../library/fps/fps.hpp"

void solve() {
    ll n, m; cin >> n >> m;
    FPS<ll> a(n), b(m);
    cin >> a; cin >> b;
    auto c = a * b;
    cout << c << endl;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << fixed << setprecision(12);
	ll T = 1;
	// cin >> T;
	while (T--) solve();
}