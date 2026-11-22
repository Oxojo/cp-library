#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "./polynomial.hpp"

/**
 * @brief Formal power series
 *
 * Adds series operations (inv/log/exp/sqrt/pow) on top of Poly.
 * Coefficients are stored as residues in [0, MOD).
 */
template <typename T = ll, int MOD = 998244353>
struct FPS : Poly<T, MOD> {
    using Base = Poly<T, MOD>;
    using Base::Base;
    using P = FPS<T, MOD>;
    static constexpr int mod = MOD;

    FPS() = default;
    FPS(const Base& b) : Base(b) {}
    FPS(Base&& b) : Base(std::move(b)) {}

    P operator+(const P& r) const { return P(Base::operator+(r)); }
    P operator+(const T& v) const { return P(Base::operator+(v)); }
    P operator-(const P& r) const { return P(Base::operator-(r)); }
    P operator-(const T& v) const { return P(Base::operator-(v)); }
    P operator*(const P& r) const { return P(Base::operator*(r)); }
    P operator*(const T& v) const { return P(Base::operator*(v)); }
    P operator/(const P& r) const { return P(Base::operator/(r)); }
    P operator%(const P& r) const { return P(Base::operator%(r)); }

    P& operator+=(const P& r) {
        Base::operator+=(r);
        return *this;
    }
    P& operator+=(const T& v) {
        Base::operator+=(v);
        return *this;
    }
    P& operator-=(const P& r) {
        Base::operator-=(r);
        return *this;
    }
    P& operator-=(const T& v) {
        Base::operator-=(v);
        return *this;
    }
    P& operator*=(const P& r) {
        Base::operator*=(r);
        return *this;
    }
    P& operator*=(const T& v) {
        Base::operator*=(v);
        return *this;
    }
    P& operator/=(const P& r) {
        Base::operator/=(r);
        return *this;
    }
    P& operator%=(const P& r) {
        Base::operator%=(r);
        return *this;
    }

    P operator-() const { return P(Base::operator-()); }

    P pre(ll def) const { return P(Base::pre(def)); }
    P rev(ll deg = -1) const { return P(Base::rev(deg)); }
    P dot(const P& r) const { return P(Base::dot(r)); }
    P diff() const { return P(Base::diff()); }
    P integral() const { return P(Base::integral()); }
    P shift(T c) const { return P(Base::shift(c)); }
    P pow_mod(ll n, const P& m) const { return P(Base::pow_mod(n, m)); }
    P operator>>(ll sz) const { return P(Base::operator>>(sz)); }
    P operator<<(ll sz) const { return P(Base::operator<<(sz)); }

    pair<P, P> div_mod(const P& r) const {
        auto qr = Base::div_mod(static_cast<const Base&>(r));
        return {P(std::move(qr.first)), P(std::move(qr.second))};
    }

    P inv(ll deg = -1) const {
        if (deg == -1) deg = (ll)this->size();
        if (deg <= 0) return P{};
        P res(polynomial_detail::inv_series(static_cast<const Base&>(*this), deg));
        res.resize(deg, T(0));
        return res;
    }

    P log(ll n = -1) const {
        if (n == -1) n = (ll)this->size();
        if (n <= 0) return P{};
        assert(this->freq(0) == T(1));
        P f = this->pre(n);
        P res = (f.diff() * f.inv(n - 1)).pre(n - 1).integral();
        res.resize(n, T(0));
        return res;
    }

    P exp(ll n = -1) const {
        if (n == -1) n = (ll)this->size();
        if (n <= 0) return P{};
        assert(this->freq(0) == T(0));

        P f = this->pre(n);
        P g{1};  // exp(f) mod x
        P h{1};  // 1 / g
        // If g == exp(f) mod x^m, then
        //   g_new = g * (1 + f - log g)  mod x^(2m).
        // Keep h = 1/g and use e = integral(f' - g'/g) to update both
        // g <- g * (1 + e), h <- h * (1 - e) in O(n log n) total.
        for (ll m = 1; m < n; m *= 2) {
            ll m2 = min(2 * m, n);

            // extend h = 1/g modulo x^m2
            h = polynomial_detail::inv_extend(static_cast<const Base&>(g),
                                              static_cast<const Base&>(h), (int)m)
                    .pre(m2);

            // w = f' - g'/g modulo x^(m2-1)
            P gp = g.diff();
            P fp = f.pre(m2).diff();
            P w = (fp - gp * h).pre(m2 - 1);

            // e = integral(w) starts at degree m; update g and h.
            P e = w.integral();
            g = (g + g * e).pre(m2);
            h = (h * (P{1} - e)).pre(m2);
        }
        g.resize(n, T(0));
        return g;
    }

    P sqrt(ll deg = -1) const {
        const ll n = (ll)this->size();
        if (n == 0) return P{};
        if (deg == -1) deg = n;
        if (deg <= 0) return P{};

        if ((*this)[0] == T(0)) {
            for (ll i = 1; i < n; ++i) {
                if ((*this)[i] != T(0)) {
                    if (i & 1) return P{};
                    if (deg - i / 2 <= 0) return P(deg);
                    P shifted = P(*this) >> i;
                    P ret = shifted.sqrt(deg - i / 2);
                    if (ret.empty()) return P{};
                    ret = (ret << (i / 2)).pre(deg);
                    ret.resize(deg, T(0));
                    return ret;
                }
            }
            return P(deg);
        }

        ll sqr = modsqrt((ll)(*this)[0], MOD);
        if (sqr == -1) return P{};
        P ret{(T)sqr};
        T inv2 = (T)modinv(2, MOD);
        for (ll i = 1; i < deg; i <<= 1) {
            ll m2 = min(2 * i, deg);
            P f = P(this->pre(m2));
            ret = ((ret + f * ret.inv(m2)) * inv2).pre(m2);
        }
        ret.resize(deg, T(0));
        return ret;
    }

    P pow(ll k, ll n = -1) const {
        assert(k >= 0);
        if (n == -1) n = (ll)this->size();
        if (n <= 0) return P{};
        if (k == 0) {
            P res(n);
            res[0] = T(1);
            return res;
        }
        if (k == 1) {
            P res = this->pre(n);
            res.resize(n, T(0));
            return res;
        }
        // Small exponents are faster by repeated squaring than by log/exp.
        if (k <= 8) {
            P base = this->pre(n);
            P res(n);
            res[0] = T(1);
            while (k > 0) {
                if (k & 1) res = (res * base).pre(n);
                k >>= 1;
                if (k) base = (base * base).pre(n);
            }
            res.resize(n, T(0));
            return res;
        }

        const ll sz = (ll)this->size();
        for (ll i = 0; i < sz; ++i) {
            if ((*this)[i] != T(0)) {
                if ((__int128)i * k >= n) return P(n);
                T rev = (T)modinv((ll)(*this)[i], MOD);
                P h = (P(*this) * rev) >> i;
                P ret = (h.log(n) * T(k)).exp(n);
                ret *= (T)modpow((ll)(*this)[i], k, (ll)MOD);
                ret = (ret << (i * k)).pre(n);
                ret.resize(n, T(0));
                return ret;
            }
            if ((__int128)(i + 1) * k >= n) return P(n);
        }
        return P(n);
    }
};
