#pragma once

#include <bits/stdc++.h>
using namespace std;

struct mint {
    using i64 = long long;
    static constexpr i64 mod = 998244353;

    i64 x;

    mint(i64 y = 0) : x(y % mod) {
        if (x < 0) x += mod;
    }

    i64 val() const { return x; }

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
        *this *= p.inv();
        return *this;
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
        i64 t;
        if (is >> t) a = mint(t);
        return is;
    }

    mint inv() const {
        assert(x != 0);
        return pow(mod - 2);
    }
    mint pow(i64 n) const {
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
