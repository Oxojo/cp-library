#pragma once

#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Rolling hash (mod 2^61 - 1)
 */
struct RollingHash {
    using ull = unsigned long long;
    static constexpr ull mod = (1ULL << 61) - 1;

    ull base;
    vector<ull> h, pw;

    explicit RollingHash(ull base_ = 1315423911ULL) : base(base_ % mod) {}

    static ull mul(ull a, ull b) {
        __uint128_t c = (__uint128_t)a * b;
        ull lo = (ull)c & mod, hi = (ull)(c >> 61);
        ull res = lo + hi;
        if (res >= mod) res -= mod;
        return res;
    }
    static ull add(ull a, ull b) {
        a += b;
        return a >= mod ? a - mod : a;
    }
    static ull sub(ull a, ull b) { return a >= b ? a - b : a + mod - b; }

    void build(const string& s) {
        int n = (int)s.size();
        h.assign(n + 1, 0);
        pw.assign(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            h[i + 1] = add(mul(h[i], base), (unsigned char)s[i]);
            pw[i + 1] = mul(pw[i], base);
        }
    }

    ull get(int l, int r) const {
        return sub(h[r], mul(h[l], pw[r - l]));
    }

    // LCP of s[a..] and s[b..], truncated to lim.
    int lcp(int a, int b, int lim) const {
        int lo = 0, hi = lim + 1;
        while (hi - lo > 1) {
            int mid = (lo + hi) / 2;
            if (get(a, a + mid) == get(b, b + mid))
                lo = mid;
            else
                hi = mid;
        }
        return lo;
    }
};
