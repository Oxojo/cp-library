#pragma once

#include "../template/template.hpp"
#include "../fps/fps.hpp"
template <class G>
struct FrequenceTreeDistance : CentroidDecomposition<G> {
	using CentroidDecomposition<G>::g;
	using CentroidDecomposition<G>::v;
	using CentroidDecomposition<G>::get_size;
	using CentroidDecomposition<G>::get_centroid;

	FrequenceTreeDistance(const G &_g) : CentroidDecomposition<G>(_g, false) {}

	FPS<ll> count, self;
	void dfs_depth(ll cur, ll par, ll d) {
		while (sz(count) <= d) count.emplace_back(0ll);
		while (sz(self) <= d) self.emplace_back(0ll);
		++count[d];
		++self[d];
		for (ll dst : g[cur]) {
			if (par == dst || v[dst]) continue;
			dfs_depth(dst, cur, d + 1);
		}
	}
	vl get(ll start = 0) {
		count.set_mod(4603910272195756033, 5);
		self.set_mod(4603910272195756033, 5);
		queue<ll> Q;
		Q.push(get_centroid(start, -1, get_size(start, -1) / 2));
		vl ans;
		ans.reserve(sz(g));
		count.reserve(sz(g));
		self.reserve(sz(g));

		while (!Q.empty()) {
			ll r = Q.front();
			Q.pop();
			count.clear();
			v[r] = 1;
			for (auto &c : g[r]) {
				if (v[c]) continue;
				self.clear();
				Q.emplace(get_centroid(c, -1, get_size(c, -1) / 2));
				dfs_depth(c, r, 1);
				auto self2 = self * self;
				while (sz(self2) > sz(ans)) ans.emplace_back(0ll);
				rep(i, sz(self2)) ans[i] -= self2[i];
			}
			if (count.empty()) continue;
			++count[0];
			auto count2 = count * count;
			while (sz(count2) > sz(ans)) ans.emplace_back(0ll);
			rep(i, sz(count2)) ans[i] += count2[i];
		}
		for (auto &x : ans) x >>= 1;
		return ans;
	}
};