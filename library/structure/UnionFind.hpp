#pragma once

#include "../template/template.hpp"
struct UnionFind {
	vl data;

	UnionFind(ll n) : data(n, -1) {}

	ll find(ll k) {
		return data[k] < 0 ? k : data[k] = find(data[k]);
	}

	ll unite(ll x, ll y) {
		x = find(x), y = find(y);
		if (x == y) return false;
		if (data[x] > data[y]) swap(x, y);
		data[x] += data[y];
		data[y] = x;
		return true;
	}

	ll size(ll k) {
		return -data[find(k)];
	}

	bool same(ll x, ll y) {
		return find(x) == find(y);
	}
};