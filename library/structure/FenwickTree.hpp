#pragma once

#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct FenwickTree {
    int n = 0;
    vector<T> data;

    FenwickTree() = default;
    explicit FenwickTree(int size) { init(size); }

    void init(int size) {
        n = size;
        data.assign(n + 1, T{});
    }

    int size() const { return n; }

    // add x to a[k] (0-indexed)
    void apply(int k, T x) {
        for (++k; k <= n; k += k & -k) data[k] += x;
    }

    // sum of [0, k]
    T prod(int k) const {
        if (k < 0) return T{};
        if (k >= n) k = n - 1;
        T ret{};
        for (++k; k > 0; k -= k & -k) ret += data[k];
        return ret;
    }

    // sum of [l, r] (closed interval)
    T prod(int l, int r) const {
        if (l > r) return T{};
        return prod(r) - prod(l - 1);
    }
};
