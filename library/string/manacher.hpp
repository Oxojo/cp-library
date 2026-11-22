#pragma once

#include <bits/stdc++.h>
using namespace std;

/// @brief Manacher's algorithm
///
/// Returns L of length 2n-1.  L[i] is the maximum length of a palindrome
/// centered at the i-th center (characters and gaps numbered from left).
vector<int> manacher(const string& s) {
    int n = (int)s.size();
    if (n == 0) return {};
    string t = "#";
    for (char c : s) {
        t += c;
        t += '#';
    }
    int m = (int)t.size();
    vector<int> r(m);
    for (int i = 0, l = 0, rr = -1; i < m; ++i) {
        int k = (i > rr) ? 1 : min(r[l + rr - i], rr - i + 1);
        while (i - k >= 0 && i + k < m && t[i - k] == t[i + k]) ++k;
        r[i] = k;
        if (i + k - 1 > rr) {
            l = i - k + 1;
            rr = i + k - 1;
        }
    }
    vector<int> res(2 * n - 1);
    for (int i = 1; i <= 2 * n - 1; ++i) res[i - 1] = r[i] - 1;
    return res;
}
