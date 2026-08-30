#pragma once

template <typename T>
struct FenwickTree {
    int n;
    vector<T> data;

    FenwickTree() = default;
    FenwickTree(int size) { init(size); }

    void init(int size) {
        n = size + 2;
        data.assign(n + 1, {});
    }

    void apply(int k, T x) {
        for (++k; k < n; k += k & -k) data[k] += x;
    }

    T prod(int k) const { // sum [0, k]
        if (k < 0) return T{};
        T ret{};
        for (++k; k > 0; k -= k & -k) ret += data[k];
        return ret;
    }
    T prod(int l, int r) const { return prod(r) - prod(l - 1); }
};