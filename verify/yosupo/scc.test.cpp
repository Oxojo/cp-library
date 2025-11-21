#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "../../library/template/template.hpp"
#include "../../library/graph/graph.hpp"
#include "../../library/graph/scc.hpp"
void solve() {
	ll n, m; cin >> n >> m;
	scc<ll> g(n);
	g.read(m, 0, 0, 1);
	g.build();
	cout << sz(g.group) << endl;
	fore(p, g.group) {
		cout << sz(p) << ' ' << p;
	}
}
int main() {
    ll T = 1;
    // cin >> T;
    while (T--) solve();
}