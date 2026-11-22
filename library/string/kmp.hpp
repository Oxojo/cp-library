#pragma once

#include <bits/stdc++.h>
using namespace std;

/// @brief Prefix function (KMP)
vector<int> prefix_function(const string& s) {
    int n = (int)s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

/// @brief KMP string matching
///
/// Returns the starting positions of all occurrences of pattern in text.
vector<int> kmp_search(const string& text, const string& pattern) {
    int m = (int)pattern.size();
    if (m == 0) return {};
    vector<int> pi = prefix_function(pattern);
    vector<int> res;
    int j = 0;
    for (int i = 0; i < (int)text.size(); ++i) {
        while (j > 0 && text[i] != pattern[j]) j = pi[j - 1];
        if (text[i] == pattern[j]) ++j;
        if (j == m) {
            res.push_back(i - m + 1);
            j = pi[j - 1];
        }
    }
    return res;
}
