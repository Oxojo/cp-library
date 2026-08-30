// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_add_range_sum

#include "../../library/template/template.hpp"
#include "../../library/structure/FenwickTree.hpp"
void solve() {
    ll n, q; cin >> n >> q;
    vl a(n); cin >> a;
    FenwickTree<ll> f(n);
    rep(i, n) f.apply(i, a[i]);
    while (q--) {
        ll t; cin >> t;
        if (t == 0) {
            ll p, x; cin >> p >> x;
            f.apply(p, x);
        }
        else {
            ll l, r; cin >> l >> r;
            r--;
            cout << f.prod(l, r) << endl;
        }
    }
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << fixed << setprecision(12);
	ll T = 1;
	// cin >> T;
	while (T--) solve();
}