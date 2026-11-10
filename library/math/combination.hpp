#pragma once

#include "./modula.hpp"

// Binomial coefficients modulo a prime (mod must be prime).
//
//   Combination comb(200000);            // mod = 998244353
//   Combination comb2(200000, 1000000007);
//   cout << comb.C(n, k) << "\n";
//
// All arguments must satisfy 0 <= n <= the value passed to the constructor
// (and n < mod for the factorial precomputation to be valid).
struct Combination {
    int n;
    ll mod;
    vector<ll> fact_, ifact_;

    explicit Combination(int n_, ll mod_ = 998244353) : n(n_), mod(mod_) {
        fact_.assign(n + 1, 1);
        ifact_.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) fact_[i] = modmul(fact_[i - 1], i, mod);
        ifact_[n] = modinv(fact_[n], mod);
        for (int i = n; i >= 1; i--) ifact_[i - 1] = modmul(ifact_[i], i, mod);
    }

    ll fact(int k) const {
        assert(0 <= k && k <= n);
        return fact_[k];
    }
    ll ifact(int k) const {
        assert(0 <= k && k <= n);
        return ifact_[k];
    }

    // nCk
    ll C(int n_, int k) const {
        if (k < 0 || n_ < k) return 0;
        assert(0 <= n_ && n_ <= n);
        return modmul(modmul(fact_[n_], ifact_[k], mod), ifact_[n_ - k], mod);
    }

    // nPk
    ll P(int n_, int k) const {
        if (k < 0 || n_ < k) return 0;
        assert(0 <= n_ && n_ <= n);
        return modmul(fact_[n_], ifact_[n_ - k], mod);
    }

    // nHk = (n + k - 1)Ck
    ll H(int n_, int k) const {
        if (n_ == 0 && k == 0) return 1 % mod;
        if (n_ <= 0 || k < 0) return 0;
        return C(n_ + k - 1, k);
    }
};
