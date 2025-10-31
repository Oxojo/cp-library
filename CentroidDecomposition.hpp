#include "template.hpp"
template <class G>
struct CentroidDecomposition {
	const G &g;
	vl sub;
	vec<bool> v;
	vv<ll> tree;
	ll root;

	CentroidDecomposition(const G &g_, bool isbuild = true) : g(g_) {
		sub.resize(sz(g), 0ll);
		v.resize(sz(g), false);
		if (isbuild) build();
	}
	void build() {
		tree.resize(sz(g));
		root = build_dfs(0);
	}
	ll get_size(ll cur, ll par) {
		sub[cur] = 1;
		for (auto &dst : g[cur]) {
			if (dst == par || v[dst]) continue;
			sub[cur] += get_size(dst, cur);
		}
		return sub[cur];
	}
	ll get_centroid(ll cur, ll par, ll mid) {
		for (auto &dst : g[cur]) {
			if (dst == par || v[dst]) continue;
			if (sub[dst] > mid) return get_centroid(dst, cur, mid);
		}
		return cur;
	}
	ll build_dfs(ll cur) {
		ll centroid = get_centroid(cur, -1, get_size(cur, -1) / 2);
		v[centroid] = true;
		for (auto &dst : g[centroid]) {
			if (!v[dst]) {
				ll nxt = build_dfs(dst);
				if (centroid != nxt) tree[centroid].emplace_back(nxt);
			}
		}
		v[centroid] = false;
		return centroid;
	}
};