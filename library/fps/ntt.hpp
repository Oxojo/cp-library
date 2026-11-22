#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "../math/modula.hpp"

/**
 * @brief Number theoretic transform and convolution
 *
 * MOD must be an NTT-friendly prime.  The primitive root is detected
 * automatically on first use.
 */
template <int MOD = 998244353>
struct NTT {
    static_assert(MOD > 2 && (MOD & 1), "MOD must be an odd prime");
    static constexpr int mod = MOD;
    static constexpr int rank2 = countr_zero((unsigned)(MOD - 1));
    static_assert(rank2 <= 31, "MOD is too large");

    using ll = long long;
    using ull = unsigned long long;

    static ll mul(ll a, ll b) { return (ull)a * b % MOD; }
    static ll add(ll a, ll b) {
        ll c = a + b;
        return c >= MOD ? c - MOD : c;
    }
    static ll sub(ll a, ll b) {
        ll c = a - b;
        return c < 0 ? c + MOD : c;
    }
    static ll power(ll a, ll e) {
        ll r = 1 % MOD;
        a %= MOD;
        while (e > 0) {
            if (e & 1) r = mul(r, a);
            a = mul(a, a);
            e >>= 1;
        }
        return r;
    }

    static int primitive_root() {
        static const int g = [] {
            int phi = MOD - 1, n = phi;
            vector<int> factors;
            for (ll p = 2; p * p <= n; ++p) {
                if (n % p == 0) {
                    factors.push_back((int)p);
                    while (n % p == 0) n /= p;
                }
            }
            if (n > 1) factors.push_back(n);
            for (int g = 2; g < MOD; ++g) {
                bool ok = true;
                for (int p : factors) {
                    if (power(g, phi / p) == 1) {
                        ok = false;
                        break;
                    }
                }
                if (ok) return g;
            }
            assert(false);
            return -1;
        }();
        return g;
    }

    struct Info {
        array<ll, 32> root{}, iroot{}, rate2{}, irate2{};

        Info() {
            int g = primitive_root();
            root[rank2] = power(g, (MOD - 1) >> rank2);
            iroot[rank2] = modinv(root[rank2], MOD);
            for (int i = rank2 - 1; i >= 0; --i) {
                root[i] = mul(root[i + 1], root[i + 1]);
                iroot[i] = mul(iroot[i + 1], iroot[i + 1]);
            }
            ll prod = 1, iprod = 1;
            for (int i = 0; i <= rank2 - 2; ++i) {
                rate2[i] = mul(root[i + 2], prod);
                irate2[i] = mul(iroot[i + 2], iprod);
                prod = mul(prod, iroot[i + 2]);
                iprod = mul(iprod, root[i + 2]);
            }
        }
    };

    static const Info& info() {
        static const Info info;
        return info;
    }

    template <typename T>
    static void butterfly(vector<T>& a) {
        int n = (int)a.size();
        int h = countr_zero((unsigned)n);
        const Info& inf = info();
        for (int ph = 1; ph <= h; ++ph) {
            int w = 1 << (ph - 1), p = 1 << (h - ph);
            ll now = 1;
            for (int s = 0; s < w; ++s) {
                int offset = s << (h - ph + 1);
                for (int i = 0; i < p; ++i) {
                    ll l = (ll)a[i + offset];
                    ll r = mul((ll)a[i + offset + p], now);
                    a[i + offset] = (T)add(l, r);
                    a[i + offset + p] = (T)sub(l, r);
                }
                if (s + 1 != w)
                    now = mul(now, inf.rate2[countr_zero((unsigned)(~s))]);
            }
        }
    }

    template <typename T>
    static void butterfly_inv(vector<T>& a) {
        int n = (int)a.size();
        int h = countr_zero((unsigned)n);
        const Info& inf = info();
        for (int ph = h; ph >= 1; --ph) {
            int w = 1 << (ph - 1), p = 1 << (h - ph);
            ll inow = 1;
            for (int s = 0; s < w; ++s) {
                int offset = s << (h - ph + 1);
                for (int i = 0; i < p; ++i) {
                    ll l = (ll)a[i + offset];
                    ll r = (ll)a[i + offset + p];
                    a[i + offset] = (T)add(l, r);
                    a[i + offset + p] = (T)mul(sub(l, r), inow);
                }
                if (s + 1 != w)
                    inow = mul(inow, inf.irate2[countr_zero((unsigned)(~s))]);
            }
        }
    }

    template <typename T>
    static vector<T> convolution(vector<T> a, vector<T> b) {
        int n = (int)a.size(), m = (int)b.size();
        if (n == 0 || m == 0) return {};
        int s = n + m - 1;

        if (min(n, m) <= 60) {
            vector<T> c(s);
            if (n > m) {
                for (int j = 0; j < m; ++j) {
                    for (int i = 0; i < n; ++i) {
                        c[i + j] = (T)((c[i + j] + (ull)a[i] * b[j]) % MOD);
                    }
                }
            } else {
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < m; ++j) {
                        c[i + j] = (T)((c[i + j] + (ull)a[i] * b[j]) % MOD);
                    }
                }
            }
            return c;
        }

        int z = 1;
        while (z < s) z <<= 1;
        assert((MOD - 1) % z == 0);

        a.resize(z);
        b.resize(z);
        butterfly(a);
        butterfly(b);
        for (int i = 0; i < z; ++i) a[i] = (T)mul((ll)a[i], (ll)b[i]);
        butterfly_inv(a);
        ll iz = modinv(z, MOD);
        a.resize(s);
        for (auto& x : a) x = (T)mul((ll)x, iz);
        return a;
    }
};
