#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "../math/modula.hpp"
#include "./ntt.hpp"

template <typename T, int MOD>
struct Poly;

namespace polynomial_detail {

template <typename T, int MOD>
Poly<T, MOD> inv_series(const Poly<T, MOD>& f, ll deg);

}  // namespace polynomial_detail

/// @brief Polynomial over Z/MODZ
///
/// Coefficients are stored as residues in [0, MOD).
/// This struct provides the ring operations (+, -, *, /, %) and
/// polynomial-specific operations such as diff/integral/shift.
template <typename T = ll, int MOD = 998244353>
struct Poly : vector<T> {
    static_assert(is_integral_v<T>, "T must be an integral type");
    static_assert(MOD >= 2, "MOD must be >= 2");

    using std::vector<T>::vector;
    using P = Poly<T, MOD>;
    static constexpr int mod = MOD;

    P pre(ll def) const {
        ll n = min((ll)this->size(), max(0LL, def));
        return P(this->begin(), this->begin() + n);
    }

    P rev(ll deg = -1) const {
        P ret(*this);
        if (deg != -1) {
            assert(deg >= 0);
            ret.resize(deg, T(0));
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }

    void shrink() {
        while (!this->empty() && !this->back()) this->pop_back();
    }

    T freq(ll p) const {
        return (0 <= p && p < (ll)this->size()) ? (*this)[p] : T(0);
    }

    P operator+(const P& r) const { return P(*this) += r; }
    P operator+(const T& v) const { return P(*this) += v; }
    P operator-(const P& r) const { return P(*this) -= r; }
    P operator-(const T& v) const { return P(*this) -= v; }
    P operator*(const P& r) const { return P(*this) *= r; }
    P operator*(const T& v) const { return P(*this) *= v; }
    P operator/(const P& r) const { return P(*this) /= r; }
    P operator%(const P& r) const { return P(*this) %= r; }

    P& operator+=(const P& r) {
        if (r.size() > this->size()) this->resize(r.size());
        for (size_t i = 0; i < r.size(); ++i) {
            ll v = (ll)(*this)[i] + (ll)r[i];
            if (v >= MOD) v -= MOD;
            (*this)[i] = (T)v;
        }
        return *this;
    }

    P& operator-=(const P& r) {
        if (r.size() > this->size()) this->resize(r.size());
        for (size_t i = 0; i < r.size(); ++i) {
            ll v = (ll)(*this)[i] - (ll)r[i];
            if (v < 0) v += MOD;
            (*this)[i] = (T)v;
        }
        return *this;
    }

    P& operator*=(const P& r) {
        if (this->empty() || r.empty()) {
            this->clear();
            return *this;
        }
        auto ret = NTT<MOD>::template convolution<T>(*this, r);
        *this = P(ret.begin(), ret.end());
        return *this;
    }

    P& operator/=(const P& r) {
        *this = div_mod(r).first;
        return *this;
    }

    P& operator%=(const P& r) {
        *this = div_mod(r).second;
        return *this;
    }

    pair<P, P> div_mod(const P& r) const {
        P d(r);
        d.shrink();
        if (d.empty()) {
            assert(false);
            return {P{}, P(*this)};
        }
        if (this->size() < d.size()) {
            P rem(*this);
            rem.shrink();
            return {P{}, rem};
        }
        ll n = (ll)this->size() - (ll)d.size() + 1;
        P q = (rev().pre(n) * polynomial_detail::inv_series(d.rev(), n))
                  .pre(n)
                  .rev(n);
        P rem = *this - q * d;
        rem.shrink();
        return {q, rem};
    }

    P operator-() const {
        P ret((ll)this->size());
        for (ll i = 0; i < (ll)this->size(); ++i)
            ret[i] = (T)((MOD - (ll)(*this)[i] % MOD) % MOD);
        return ret;
    }

    P& operator+=(const T& v) {
        if (this->empty()) this->resize(1);
        ll add = ((ll)v % MOD + MOD) % MOD;
        ll nv = (ll)(*this)[0] + add;
        if (nv >= MOD) nv -= MOD;
        (*this)[0] = (T)nv;
        return *this;
    }

    P& operator-=(const T& v) {
        if (this->empty()) this->resize(1);
        ll sub = ((ll)v % MOD + MOD) % MOD;
        ll nv = (ll)(*this)[0] - sub;
        if (nv < 0) nv += MOD;
        (*this)[0] = (T)nv;
        return *this;
    }

    P& operator*=(const T& v) {
        ll m = ((ll)v % MOD + MOD) % MOD;
        for (ll i = 0; i < (ll)this->size(); ++i)
            (*this)[i] = (T)((ll)(*this)[i] * m % MOD);
        return *this;
    }

    // coefficient-wise product (shorter length)
    P dot(const P& r) const {
        P ret(min(this->size(), r.size()));
        for (ll i = 0; i < (ll)ret.size(); ++i)
            ret[i] = (T)((ll)(*this)[i] * (ll)r[i] % MOD);
        return ret;
    }

    P operator>>(ll sz) const {
        assert(sz >= 0);
        if ((ll)this->size() <= sz) return {};
        P ret(*this);
        ret.erase(ret.begin(), ret.begin() + sz);
        return ret;
    }

    P operator<<(ll sz) const {
        assert(sz >= 0);
        P ret(*this);
        ret.insert(ret.begin(), sz, T(0));
        return ret;
    }

    // evaluate at x (modular)
    T operator()(T x) const {
        ll r = 0, w = 1, xx = ((ll)x % MOD + MOD) % MOD;
        for (auto& v : *this) {
            r = (r + w * (ll)v) % MOD;
            w = w * xx % MOD;
        }
        return (T)r;
    }

    P diff() const {
        const ll n = (ll)this->size();
        if (n <= 1) return {};
        P ret(n - 1);
        for (ll i = 1; i < n; ++i)
            ret[i - 1] = (T)modmul((ll)(*this)[i], i, MOD);
        return ret;
    }

    P integral() const {
        const ll n = (ll)this->size();
        if (n == 0) return {};
        P ret(n + 1);
        vector<ll> inv(n + 1);
        if (n < MOD) {
            inv[1] = 1;
            for (ll i = 2; i <= n; ++i)
                inv[i] = (ll)(MOD - (ll)(MOD / i) * inv[MOD % i] % MOD);
        } else {
            for (ll i = 1; i <= n; ++i) inv[i] = modinv(i, MOD);
        }
        for (ll i = 0; i < n; ++i)
            ret[i + 1] = (T)((ll)(*this)[i] * inv[i + 1] % MOD);
        return ret;
    }

    P pow_mod(ll n, const P& m) const {
        assert(n >= 0);
        P x(*this), r{1};
        while (n > 0) {
            if (n & 1) r = r * x % m;
            x = x * x % m;
            n >>= 1;
        }
        return r;
    }

    // Taylor shift: returns f(x + c)
    P shift(T c) const {
        const ll n = (ll)this->size();
        if (n == 0) return {};
        vector<T> fact(n), rfact(n);
        fact[0] = rfact[0] = T(1);
        for (ll i = 1; i < n; ++i)
            fact[i] = (T)modmul((ll)fact[i - 1], i, MOD);
        rfact[n - 1] = (T)modinv((ll)fact[n - 1], MOD);
        for (ll i = n - 1; i >= 2; --i)
            rfact[i - 1] = (T)modmul((ll)rfact[i], i, MOD);
        ll cc = ((ll)c % MOD + MOD) % MOD;
        P p(*this);
        for (ll i = 0; i < n; ++i)
            p[i] = (T)modmul((ll)p[i], (ll)fact[i], MOD);
        p = p.rev();
        P bs(n, T(1));
        for (ll i = 1; i < n; ++i)
            bs[i] = (T)modmul((ll)bs[i - 1],
                              modmul(cc, modmul((ll)rfact[i], (ll)fact[i - 1], MOD),
                                     MOD),
                              MOD);
        p = (p * bs).pre(n);
        p = p.rev();
        for (ll i = 0; i < n; ++i)
            p[i] = (T)modmul((ll)p[i], (ll)rfact[i], MOD);
        return p;
    }
};

namespace polynomial_detail {

// h = 1/f mod x^m -> 1/f mod x^(2m)
template <typename T, int MOD>
Poly<T, MOD> inv_extend(const Poly<T, MOD>& f, const Poly<T, MOD>& h, int m) {
    using P = Poly<T, MOD>;
    using N = NTT<MOD>;
    int m2 = 2 * m;
    assert((MOD - 1) % m2 == 0);
    vector<T> a(m2), b(m2);
    int fn = min(m2, (int)f.size());
    for (int i = 0; i < fn; ++i) a[i] = f[i];
    for (int i = 0; i < m; ++i) b[i] = h.freq(i);
    N::butterfly(a);
    N::butterfly(b);
    for (int i = 0; i < m2; ++i) a[i] = (T)N::mul((ll)a[i], (ll)b[i]);
    N::butterfly_inv(a);
    ll iz = modinv(m2, MOD);
    for (int i = 0; i < m; ++i) a[i] = (T)N::mul((ll)a[m + i], iz);
    fill(a.begin() + m, a.end(), T(0));
    N::butterfly(a);
    for (int i = 0; i < m2; ++i) a[i] = (T)N::mul((ll)a[i], (ll)b[i]);
    N::butterfly_inv(a);
    P res(m2);
    for (int i = 0; i < m; ++i) {
        res[i] = h.freq(i);
        T v = (T)N::mul((ll)a[i], iz);
        res[m + i] = v ? (T)(MOD - v) : T(0);
    }
    return res;
}

template <typename T, int MOD>
Poly<T, MOD> inv_series(const Poly<T, MOD>& f, ll deg) {
    using P = Poly<T, MOD>;
    if (deg <= 0) return P{};
    assert(f.freq(0) != T(0));
    P res{(T)modinv((ll)f.freq(0), MOD)};
    int m = 1;
    while (m < deg) {
        res = inv_extend(f, res, m);
        m *= 2;
    }
    res.resize(deg, T(0));
    return res;
}

}  // namespace polynomial_detail

