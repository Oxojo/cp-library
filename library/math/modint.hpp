#pragma once

#include <bits/stdc++.h>
using namespace std;

// mod must be prime for inv() / division
template <int m>
struct modint {
    static_assert(m >= 2, "mod must be >= 2");

    static constexpr int mod = m;
    using mint = modint<m>;

    long long x;

    modint(long long y = 0) : x(y % mod) {
        if (x < 0) x += mod;
    }

    long long val() const { return x; }
    explicit operator bool() const { return x != 0; }

    mint &operator+=(const mint &p) {
        if ((x += p.x) >= mod) x -= mod;
        return *this;
    }
    mint &operator-=(const mint &p) {
        if ((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }
    mint &operator*=(const mint &p) {
        x = x * p.x % mod;
        return *this;
    }
    mint &operator/=(const mint &p) {
        assert(p.x != 0);
        return *this *= p.inv();
    }

    mint operator-() const { return mint(-x); }
    mint operator+(const mint &p) const { return mint(*this) += p; }
    mint operator-(const mint &p) const { return mint(*this) -= p; }
    mint operator*(const mint &p) const { return mint(*this) *= p; }
    mint operator/(const mint &p) const { return mint(*this) /= p; }

    bool operator==(const mint &p) const { return x == p.x; }
    bool operator!=(const mint &p) const { return x != p.x; }

    friend ostream &operator<<(ostream &os, const mint &p) { return os << p.x; }
    friend istream &operator>>(istream &is, mint &a) {
        long long t;
        if (is >> t) a = mint(t);
        return is;
    }

    mint inv() const {
        assert(x != 0);
        return pow(mod - 2);
    }
    mint pow(long long n) const {
        assert(n >= 0);
        mint ret(1), mul(x);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }
};

using mint = modint<998244353>;
