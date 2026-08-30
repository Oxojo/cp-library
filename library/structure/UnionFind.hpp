#pragma once

struct UnionFind {
    vector<int> data;
    UnionFind(ll n) : data(n, -1) {}

    int root(int k) {
        return data[k] < 0 ? k : data[k] = root(data[k]);
    }

    bool unite(int x, int y) {
        x = root(x); y = root(y);
        if (x == y) return false;
        if (data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    int size(int k) {
        return -data[root(k)];
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    }
};