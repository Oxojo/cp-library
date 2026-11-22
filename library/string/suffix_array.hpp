#pragma once

#include <bits/stdc++.h>
using namespace std;

namespace suffix_array_detail {

// a[i] is an arbitrary integer rank.  A unique sentinel -1 is appended.
inline vector<int> build(vector<int> a) {
    int n = (int)a.size();
    a.push_back(-1);
    int m = n + 1;

    vector<int> p(m), c(m);
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](int i, int j) { return a[i] < a[j]; });

    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < m; ++i) {
        if (a[p[i]] != a[p[i - 1]]) ++classes;
        c[p[i]] = classes - 1;
    }

    vector<int> pn(m), cn(m), cnt(m);
    for (int len = 1; len < m; len <<= 1) {
        for (int i = 0; i < m; ++i) {
            pn[i] = p[i] - len;
            if (pn[i] < 0) pn[i] += m;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < m; ++i) ++cnt[c[pn[i]]];
        for (int i = 1; i < classes; ++i) cnt[i] += cnt[i - 1];
        for (int i = m - 1; i >= 0; --i) p[--cnt[c[pn[i]]]] = pn[i];

        cn[p[0]] = 0;
        int nc = 1;
        for (int i = 1; i < m; ++i) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + len) % m]};
            pair<int, int> prv = {c[p[i - 1]], c[(p[i - 1] + len) % m]};
            if (cur != prv) ++nc;
            cn[p[i]] = nc - 1;
        }
        c.swap(cn);
        classes = nc;
    }

    // remove the suffix starting at the sentinel
    return vector<int>(p.begin() + 1, p.end());
}

}  // namespace suffix_array_detail

/**
 * @brief Suffix array
 *
 * Accepts a string or a vector of integers.
 * Complexity: O(n log n).
 */
inline vector<int> suffix_array(const string& s) {
    return suffix_array_detail::build(vector<int>(s.begin(), s.end()));
}

template <typename Container>
vector<int> suffix_array(const Container& s) {
    int n = (int)s.size();
    vector<typename Container::value_type> vals(s.begin(), s.end());
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        a[i] = (int)(lower_bound(vals.begin(), vals.end(), s[i]) - vals.begin());
    return suffix_array_detail::build(std::move(a));
}

/**
 * @brief LCP array (Kasai)
 *
 * lcp[i] = LCP(s[sa[i]..], s[sa[i+1]..]).
 */
template <typename Container>
vector<int> lcp_array(const Container& s, const vector<int>& sa) {
    int n = (int)s.size();
    if (n <= 1) return {};
    vector<int> rnk(n), lcp(n - 1);
    for (int i = 0; i < n; ++i) rnk[sa[i]] = i;
    int h = 0;
    for (int i = 0; i < n; ++i) {
        int r = rnk[i];
        if (r == 0) continue;
        int j = sa[r - 1];
        while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;
        lcp[r - 1] = h;
        if (h > 0) --h;
    }
    return lcp;
}
