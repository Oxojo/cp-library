// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/unionfind

#include "../../library/template/template.hpp"
#include "../../library/structure/UnionFind.hpp"

void solve() {
	ll n, q; in(n, q);
	UnionFind uf(n);
	while (q--) {
		ll t, u, v; in(t, u, v);
		if (t == 0) {
			uf.unite(u, v);
		}
		else {
			out(uf.same(u, v), "\n");
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