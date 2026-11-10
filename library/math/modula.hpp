#pragma once

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T>
T safe_mod(T a, T p) {
    a %= p;
    return a < 0 ? a + p : a;
}

// (a * b) % mod without overflow
inline ll modmul(ll a, ll b, ll mod) { return (ll)((__int128)a * b % mod); }

// a^n mod p
template <typename T, typename U>
T modpow(T a, U n, T p) {
    a = safe_mod(a, p);
    T ret = T(1) % p;
    while (n > 0) {
        if (n & 1) ret = (T)((__int128)ret * a % p);
        a = (T)((__int128)a * a % p);
        n >>= 1;
    }
    return ret;
}

// inverse of x modulo mod (requires gcd(x, mod) == 1)
inline ll modinv(ll x, ll mod) {
    __int128 a = safe_mod(x, mod), b = mod, u = 1, v = 0;
    while (b) {
        __int128 t = a / b;
        a -= t * b;
        swap(a, b);
        u -= t * v;
        swap(u, v);
    }
    assert(a == 1);
    __int128 r = u % mod;
    if (r < 0) r += mod;
    return (ll)r;
}

// smallest x >= 0 such that a^x == b (mod p), or -1 if it does not exist
// (extended baby-step giant-step; works for composite p as well)
template <typename T>
T modlog(T a_, T b_, T p_) {
    ll p = (ll)p_;
    if (p == 1) return 0;
    ll a = safe_mod((ll)a_, p), b = safe_mod((ll)b_, p);
    if (b == 1 % p) return 0;
    if (a == 0) return (b == 0) ? 1 : -1;

    // strip the common factors of a and p
    ll x0 = 0, mul = 1;
    for (;;) {
        ll g = gcd(a, p);
        if (g == 1) break;
        if (b == mul) return (T)x0;
        if (b % g != 0) return (T)-1;
        b /= g;
        p /= g;
        mul = modmul(mul, a / g, p);
        ++x0;
        if (p == 1) return (T)x0;
    }

    // now gcd(a, p) == 1: solve a^y == b * mul^{-1} (mod p)
    ll target = modmul(b, modinv(mul, p), p);
    ll n = (ll)sqrt((long double)p) + 1;
    unordered_map<ll, ll> tbl;
    tbl.reserve(n * 2);
    ll e = 1;
    for (ll j = 0; j < n; ++j) {
        if (!tbl.count(e)) tbl[e] = j;
        e = modmul(e, a, p);
    }
    ll step = modinv(e, p);  // a^{-n}
    ll cur = target;
    for (ll i = 0; i <= n; ++i) {
        auto it = tbl.find(cur);
        if (it != tbl.end()) return (T)(x0 + i * n + it->second);
        cur = modmul(cur, step, p);
    }
    return (T)-1;
}

// x such that x^2 == a (mod p), or -1 if it does not exist
// (p must be an odd prime)
inline ll modsqrt(ll a, ll p) {
    a %= p;
    if (a < 0) a += p;
    if (a == 0) return 0;
    if (p == 2) return a;
    if (modpow(a, (p - 1) / 2, p) != 1) return -1;
    if (p % 4 == 3) return modpow(a, (p + 1) / 4, p);
    ll s = p - 1, n = 2;
    ll r = 0, m;
    while (s % 2 == 0) ++r, s /= 2;
    while (modpow(n, (p - 1) / 2, p) != p - 1) ++n;
    ll x = modpow(a, (s + 1) / 2, p);
    ll b = modpow(a, s, p), g = modpow(n, s, p);
    for (;; r = m) {
        ll t = b;
        for (m = 0; m < r && t != 1; ++m) t = modmul(t, t, p);
        if (m == 0) return x;
        ll gs = modpow(g, 1ll << (r - m - 1), p);
        g = modmul(gs, gs, p);
        x = modmul(x, gs, p);
        b = modmul(b, g, p);
    }
}
