#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../../template.hpp"
#include "../../FenwickTree.hpp"
void solve() {
    ll n, q; cin >> n >> q;
    vl a(n); cin >> a;
    FenwickTree f(a);
    while (q--) {
        ll t; cin >> t;
        if (t == 0) {
            ll p, x; cin >> p >> x;
            f.add(p, x);
        }
        else {
            ll l, r; cin >> l >> r;
            r--;
            cout << f.sum(l, r) << endl;
        }
    }
}
int main() {
    ll T = 1;
    // cin >> T;
    while (T--) solve();
}