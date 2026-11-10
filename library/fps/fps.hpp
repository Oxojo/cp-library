#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "../math/modula.hpp"

template <typename T = ll>
struct FPS : vector<T> {
private:
    ll mod = 998244353;
    ll root = 3;

    void ntt(vector<T>& a) {
        int n = (int)a.size();
        int L = 31 - __builtin_clz((unsigned)n);
        vector<ll> rt(2, 1);
        for (ll k = 2, s = 2; k < n; k *= 2, s++) {
            rt.resize(n);
            ll z[] = {1, modpow(root, mod >> s, mod)};
            for (ll i = k; i < 2 * k; i++) rt[i] = modmul(rt[i / 2], z[i & 1], mod);
        }
        vector<int> rev(n);
        for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
        for (int i = 0; i < n; i++)
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k *= 2) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    ll z = modmul(rt[j + k], (ll)a[i + j + k], mod);
                    ll ai = (ll)a[i + j];
                    a[i + j + k] = (T)(ai - z + (z > ai ? mod : 0));
                    a[i + j] = (T)(ai + (ai + z >= mod ? z - mod : z));
                }
            }
        }
    }

    vector<T> conv(const vector<T>& a, const vector<T>& b) {
        if (a.empty() || b.empty()) return {};
        ll s = (ll)a.size() + (ll)b.size() - 1;
        assert(s <= (1LL << 23));  // NTT-friendly upper bound for 998244353
        int B = 0;
        while ((1LL << B) < s) ++B;
        int n = 1 << B;
        ll inv = modinv(n, mod);
        vector<T> L(a), R(b), out(n);
        L.resize(n);
        R.resize(n);
        ntt(L);
        ntt(R);
        for (int i = 0; i < n; i++)
            out[(-i) & (n - 1)] = (T)modmul((ll)L[i], modmul((ll)R[i], inv, mod), mod);
        ntt(out);
        out.resize(s);
        return out;
    }

public:
    using std::vector<T>::vector;
    using P = FPS;

    // set_mod is only meaningful for NTT-friendly moduli (root must be a primitive root)
    void set_mod(ll md, ll g) {
        mod = md;
        root = g;
    }

    P pre(ll def) const {
        ll n = min((ll)this->size(), max(0LL, def));
        return P(this->begin(), this->begin() + n);
    }
    P rev(ll deg = -1) const {
        P ret(*this);
        if (deg != -1) ret.resize(deg, T(0));
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
        for (size_t i = 0; i < r.size(); i++) {
            ll v = (ll)(*this)[i] + (ll)r[i];
            if (v >= mod) v -= mod;
            (*this)[i] = (T)v;
        }
        return *this;
    }
    P& operator-=(const P& r) {
        if (r.size() > this->size()) this->resize(r.size());
        for (size_t i = 0; i < r.size(); i++) {
            ll v = (ll)(*this)[i] - (ll)r[i];
            if (v < 0) v += mod;
            (*this)[i] = (T)v;
        }
        return *this;
    }

    P& operator*=(const P& r) {
        if (this->empty() || r.empty()) {
            this->clear();
            return *this;
        }
        auto ret = conv(*this, r);
        *this = P(ret.begin(), ret.end());
        return *this;
    }
    P& operator/=(const P& r) {
        if (this->size() < r.size()) {
            this->clear();
            return *this;
        }
        ll n = (ll)this->size() - (ll)r.size() + 1;
        return *this = (rev().pre(n) * r.rev().inv(n)).pre(n).rev(n);
    }
    P& operator%=(const P& r) {
        *this -= *this / r * r;
        shrink();
        return *this;
    }
    pair<P, P> div_mod(const P& r) {
        P q = *this / r;
        P x = *this - q * r;
        x.shrink();
        return make_pair(q, x);
    }
    P operator-() const {
        P ret((ll)this->size());
        for (ll i = 0; i < (ll)this->size(); i++) ret[i] = (T)((-(*this)[i] % mod + mod) % mod);
        return ret;
    }

    P& operator+=(const T& v) {
        if (this->empty()) this->resize(1);
        ll add = ((ll)v % mod + mod) % mod;
        ll nv = (ll)(*this)[0] + add;
        if (nv >= mod) nv -= mod;
        (*this)[0] = (T)nv;
        return *this;
    }
    P& operator-=(const T& v) {
        if (this->empty()) this->resize(1);
        ll sub = ((ll)v % mod + mod) % mod;
        ll nv = (ll)(*this)[0] - sub;
        if (nv < 0) nv += mod;
        (*this)[0] = (T)nv;
        return *this;
    }
    P& operator*=(const T& v) {
        ll m = ((ll)v % mod + mod) % mod;
        for (ll i = 0; i < (ll)this->size(); i++) (*this)[i] = (T)modmul((ll)(*this)[i], m, mod);
        return *this;
    }

    // coefficient-wise product (shorter length)
    P dot(P r) const {
        P ret(min(this->size(), r.size()));
        for (ll i = 0; i < (ll)ret.size(); i++) ret[i] = (T)modmul((ll)(*this)[i], (ll)r[i], mod);
        return ret;
    }

    P operator>>(ll sz) const {
        if ((ll)this->size() <= sz) return {};
        P ret(*this);
        ret.erase(ret.begin(), ret.begin() + sz);
        return ret;
    }
    P operator<<(ll sz) const {
        P ret(*this);
        ret.insert(ret.begin(), sz, T(0));
        return ret;
    }

    // evaluate at x (modular)
    T operator()(T x) const {
        ll r = 0, w = 1, xx = ((ll)x % mod + mod) % mod;
        for (auto& v : *this) {
            r = (r + w * (ll)v) % mod;
            w = w * xx % mod;
        }
        return (T)r;
    }

    P diff() const {
        const ll n = (ll)this->size();
        P ret(max(0LL, n - 1));
        for (ll i = 1; i < n; i++) ret[i - 1] = (T)modmul((ll)(*this)[i], i, mod);
        return ret;
    }
    P integral() const {
        const ll n = (ll)this->size();
        P ret(n + 1);
        for (ll i = 0; i < n; i++) ret[i + 1] = (T)modmul((ll)freq(i), modinv(i + 1, mod), mod);
        return ret;
    }
    P inv(ll deg = -1) const {
        if (deg == -1) deg = (ll)this->size();
        assert(freq(0) != T(0));
        P res = P({(T)modinv(freq(0), mod)});
        for (ll i = 1; i < deg; i *= 2) {
            res = (res * T(2) - res * res * pre(2 * i)).pre(2 * i);
        }
        return res.pre(deg);
    }
    P exp(ll n = -1) const {
        assert(freq(0) == T(0));
        if (n == -1) n = (ll)this->size();
        P g = P({T(1)});
        for (ll i = 1; i < n; i *= 2) {
            g = (g * (pre(i * 2) + P({T(1)}) - g.log(i * 2))).pre(i * 2);
        }
        return g.pre(n);
    }
    P log(ll n = -1) const {
        if (n == -1) n = (ll)this->size();
        assert(freq(0) == T(1));
        auto f = pre(n);
        return (f.diff() * f.inv(n - 1)).pre(n - 1).integral();
    }
    P sqrt(ll deg = -1) const {
        const ll n = (ll)this->size();
        if (n == 0) return {};
        if (deg == -1) deg = n;
        if ((*this)[0] == T(0)) {
            for (ll i = 1; i < n; i++) {
                if ((*this)[i] != T(0)) {
                    if (i & 1) return {};
                    if (deg - i / 2 <= 0) break;
                    auto ret = (*this >> i).sqrt(deg - i / 2);
                    if (ret.empty()) return {};
                    ret = ret << (i / 2);
                    if ((ll)ret.size() < deg) ret.resize(deg, T(0));
                    return ret;
                }
            }
            return P(deg);
        }
        auto sqr = T(modsqrt((*this)[0], mod));
        ll d = modmul(sqr, sqr, mod) - (ll)(*this)[0];
        if (((d % mod) + mod) % mod != 0) return {};
        P ret{sqr};
        T inv2 = (T)modinv(T(2), mod);
        for (ll i = 1; i < deg; i <<= 1) {
            ret = (ret + pre(i << 1) * ret.inv(i << 1)) * inv2;
        }
        return ret.pre(deg);
    }
    P pow(ll k, ll n = -1) {
        assert(k >= 0);
        if (n == -1) n = (ll)this->size();
        if (k == 0) {
            P res(n);
            res[0] = T(1);
            return res;
        }
        for (ll i = 0; i < (ll)this->size(); i++) {
            if ((*this)[i]) {
                T rev = (T)modinv((*this)[i], mod);
                P ret = (((*this * rev) >> i).log(n) * T(k)).exp(n);
                ret *= (T)modpow((ll)(*this)[i], k, mod);
                ret = (ret << (i * k)).pre(n);
                if ((ll)ret.size() < n) ret.resize(n);
                return ret;
            }
            if (__int128(i + 1) * k >= n) return P(n);
        }
        return P(n);
    }
    P pow_mod(ll n, const P& m) {
        P x = *this, r = {{1}};
        while (n) {
            if (n & 1) r = r * x % m;
            x = x * x % m;
            n >>= 1;
        }
        return r;
    }
    // Taylor shift: returns f(x + c)
    P shift(T c) const {
        ll n = (ll)this->size();
        vector<T> fact(n), rfact(n);
        fact[0] = rfact[0] = T(1);
        for (ll i = 1; i < n; i++) fact[i] = (T)modmul((ll)fact[i - 1], i, mod);
        rfact[n - 1] = T(1) * (T)modinv(fact[n - 1], mod);
        for (ll i = n - 1; i >= 2; i--) rfact[i - 1] = (T)modmul(rfact[i], i, mod);
        ll cc = ((ll)c % mod + mod) % mod;
        P p(*this);
        for (ll i = 0; i < n; i++) p[i] = (T)modmul((ll)p[i], (ll)fact[i], mod);
        p = p.rev();
        P bs(n, T(1));
        for (ll i = 1; i < n; i++)
            bs[i] = (T)modmul((ll)bs[i - 1], modmul(cc, modmul((ll)rfact[i], (ll)fact[i - 1], mod), mod), mod);
        p = (p * bs).pre(n);
        p = p.rev();
        for (ll i = 0; i < n; i++) p[i] = (T)modmul((ll)p[i], (ll)rfact[i], mod);
        return p;
    }
};
