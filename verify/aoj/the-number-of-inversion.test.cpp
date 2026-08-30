// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_5_D

#include "../../library/template/template.hpp"
#include "../../library/structure/FenwickTree.hpp"
#include "../../library/dp/inversion_number.hpp"

void solve() {
    int n; cin >> n;
    vl a(n); cin >> a;
    cout << inversion_num(a) << endl;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << fixed << setprecision(12);
	ll T = 1;
	// cin >> T;
	while (T--) solve();
}