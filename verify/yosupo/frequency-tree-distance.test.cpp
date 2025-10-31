#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"

#include "../../library/template/template.hpp"
#include "../../library/math/modula.hpp"
#include "../../library/fps/fps.hpp"
#include "../../library/tree/CentroidDecomposition.hpp"
#include "../../library/tree/FrequencyTreeDistance.hpp"
void solve() {
	ll N; cin >> N;
	vv<ll> G(N);
	rep(i, N - 1) {
		ll u, v; cin >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	FrequenceTreeDistance<vv<ll>> ft(G);
	auto d = ft.get();
	d.resize(N);
	reps(i, 1, N) {
		if (i != 1) cout << ' ';
		cout << d[i];
	}
	cout << endl;
}
int main() {
	ll T = 1;
	// cin >> T;
	while (T--) solve();
}