#pragma once

#include <utility>
#include <vector>

struct UnionFind {
    std::vector<int> data;
    explicit UnionFind(int n = 0) : data(n, -1) {}

    int root(int k) {
        return data[k] < 0 ? k : data[k] = root(data[k]);
    }

    int root(int k) const {
        while (data[k] >= 0) k = data[k];
        return k;
    }

    bool unite(int x, int y) {
        x = root(x); y = root(y);
        if (x == y) return false;
        if (data[x] > data[y]) std::swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    int size(int k) { return -data[root(k)]; }
    int size(int k) const { return -data[root(k)]; }

    bool same(int x, int y) { return root(x) == root(y); }
    bool same(int x, int y) const { return root(x) == root(y); }
};
