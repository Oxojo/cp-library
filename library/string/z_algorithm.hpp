#pragma once

#include <bits/stdc++.h>
using namespace std;

/// @brief Z algorithm
///
/// z[i] = LCP(s, s[i..]) for i > 0, and z[0] = n.
template <typename T>
vector<int> z_algorithm(const T& s) {
    int n = (int)s.size();
    vector<int> z(n);
    if (n == 0) return z;
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}
