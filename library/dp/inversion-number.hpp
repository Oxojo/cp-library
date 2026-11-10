#pragma once

#include <algorithm>
#include <vector>

#include "../structure/FenwickTree.hpp"

template <typename T>
long long inversion_num(const std::vector<T>& v) {
    std::vector<T> x{v};
    std::sort(x.begin(), x.end());
    x.erase(std::unique(x.begin(), x.end()), x.end());
    int s = (int)x.size();

    FenwickTree<long long> bit(s + 1);
    long long res = 0;
    for (auto& p : v) {
        int it = (int)(std::lower_bound(x.begin(), x.end(), p) - x.begin());
        if (it + 1 != s) res += bit.prod(it + 1, s - 1);
        bit.apply(it, 1);
    }
    return res;
}
