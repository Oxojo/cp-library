#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "../../library/template/template.hpp"
#include "../../library/structure/UnionFind.hpp"

void solve() {
    ll n, q; cin >> n >> q;
	UnionFind uf(n);
	while (q--) {
		ll t; cin >> t;
		if (t == 0) {
			ll u, v; cin >> u >> v;
			uf.unite(u, v);
		}
		else {
			ll u, v; cin >> u >> v;
			cout << uf.same(u, v) << endl;
		}
	}
}
int main() {
    ll T = 1;
    // cin >> T;
    while (T--) solve();
}