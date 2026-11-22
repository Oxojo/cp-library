#pragma once

#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Fenwick tree
 *
 * Intervals are half-open: [l, r).
 */
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

    // sum of [0, r)
    T prod(int r) const {
        if (r <= 0) return T{};
        if (r > n) r = n;
        T ret{};
        for (; r > 0; r -= r & -r) ret += data[r];
        return ret;
    }

    // sum of [l, r)
    T prod(int l, int r) const {
        if (l >= r) return T{};
        return prod(r) - prod(l);
    }
};
