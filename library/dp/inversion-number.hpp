#pragma once

#include "../structure/FenwickTree.hpp"

template <typename T>
long long inversion_num(const vector<T> &v) {
    vector<T> x{v};
    sort(begin(x), end(x));
    x.erase(unique(begin(x), end(x)), end(x));
    int s = (int)x.size();

    FenwickTree<long long> bit(s + 1);
    long long res = 0;
    for (auto &p : v) {
        int it = lower_bound(begin(x), end(x)) - begin(x);
        if (it + 1 != s) res += bit.prod(it + 1, s - 1);
        bit.apply(it, 1);
    } 
    return res;
}