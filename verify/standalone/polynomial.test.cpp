// competitive-verifier: STANDALONE

#include "../../library/fps/fps.hpp"

#include <random>

#define CHECK(x)                                                         \
    do {                                                                 \
        if (!(x)) {                                                      \
            cerr << "FAILED: " #x << " (line " << __LINE__ << ")" << endl; \
            return 1;                                                    \
        }                                                                \
    } while (0)

namespace {

constexpr int MOD = 998244353;
using ll = long long;

std::mt19937_64 rng(20261122);

ll mul(ll a, ll b) { return (unsigned long long)a * b % MOD; }

ll power(ll a, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e & 1) r = mul(r, a);
        a = mul(a, a);
        e >>= 1;
    }
    return r;
}

vector<ll> naive_conv(const vector<ll>& a, const vector<ll>& b) {
    if (a.empty() || b.empty()) return {};
    vector<ll> c(a.size() + b.size() - 1);
    for (int i = 0; i < (int)a.size(); i++)
        for (int j = 0; j < (int)b.size(); j++)
            c[i + j] = (c[i + j] + mul(a[i], b[j])) % MOD;
    return c;
}

ll shift_naive(const FPS<ll>& a, ll c, int idx) {
    ll res = 0;
    ll comb = 1;
    for (int k = idx; k < (int)a.size(); k++) {
        res = (res + mul(mul(a[k], comb), power(c, k - idx))) % MOD;
        comb = mul(mul(comb, k + 1), power(k + 1 - idx, MOD - 2));
    }
    return res;
}

}  // namespace

int main() {
    // NTT / convolution
    for (int tc = 0; tc < 80; tc++) {
        int n = (int)(rng() % 90) + 1;
        int m = (int)(rng() % 90) + 1;
        vector<ll> a(n), b(m);
        for (auto& x : a) x = rng() % MOD;
        for (auto& x : b) x = rng() % MOD;
        CHECK(NTT<MOD>::convolution(a, b) == naive_conv(a, b));
    }

    // Polynomial ring operations
    for (int tc = 0; tc < 60; tc++) {
        int n = (int)(rng() % 35) + 1;
        int m = (int)(rng() % 35) + 1;
        Poly<ll> a(n), b(m);
        for (auto& x : a) x = rng() % MOD;
        for (auto& x : b) x = rng() % MOD;

        auto sum = a + b;
        auto dif = a - b;
        for (int i = 0; i < max(n, m); i++) {
            CHECK(sum.freq(i) == (a.freq(i) + b.freq(i)) % MOD);
            CHECK(dif.freq(i) == (a.freq(i) - b.freq(i) + MOD) % MOD);
        }
        CHECK(vector<ll>(a * b) == naive_conv(a, b));

        auto dot = a.dot(b);
        for (int i = 0; i < min(n, m); i++)
            CHECK(dot[i] == mul(a[i], b[i]));

        auto integ = a.integral();
        auto deriv = integ.diff();
        for (int i = 0; i < (int)a.size(); i++) CHECK(deriv.freq(i) == a[i]);

        ll c = rng() % MOD;
        FPS<ll> af(a.begin(), a.end());
        auto sh = af.shift(c);
        for (int i = 0; i < n; i++)
            CHECK(sh[i] == shift_naive(af, c, i));
    }
    {
        Poly<ll> empty;
        CHECK(empty.shift(3).empty());
        CHECK(empty.diff().empty());
        CHECK(empty.integral().empty());
        CHECK(empty.pre(5).empty());
        CHECK(empty.rev().empty());
    }

    // polynomial division / remainder
    for (int tc = 0; tc < 60; tc++) {
        int n = (int)(rng() % 40) + 1;
        int m = (int)(rng() % 20) + 1;
        Poly<ll> a(n), b(m);
        for (auto& x : a) x = rng() % MOD;
        for (auto& x : b) x = rng() % MOD;
        b[m - 1] = 1 + rng() % (MOD - 1);
        auto qr = a.div_mod(b);
        auto rec = qr.first * b + qr.second;
        for (int i = 0; i < n; i++) CHECK(rec.freq(i) == a[i]);
        CHECK(qr.second.empty() || qr.second.size() < b.size());
    }

    // FPS inv / log / exp
    for (int tc = 0; tc < 50; tc++) {
        int n = (int)(rng() % 50) + 1;
        FPS<ll> f(n);
        for (auto& x : f) x = rng() % MOD;
        f[0] = 1 + rng() % (MOD - 1);

        auto inv = f.inv(n);
        auto prod = f * inv;
        for (int i = 0; i < n; i++) CHECK(prod.freq(i) == (i == 0));
    }

    for (int tc = 0; tc < 50; tc++) {
        int n = (int)(rng() % 50) + 1;
        FPS<ll> f(n);
        for (auto& x : f) x = rng() % MOD;
        f[0] = 1 + rng() % (MOD - 1);
        f *= (ll)power(f[0], MOD - 2);

        auto l = f.log(n);
        auto e = l.exp(n);
        for (int i = 0; i < n; i++) CHECK(e.freq(i) == f.freq(i));
    }

    // exp vs the defining differential equation, including f[0] == 0
    for (int tc = 0; tc < 50; tc++) {
        int n = (int)(rng() % 50) + 1;
        FPS<ll> f(n);
        for (auto& x : f) x = rng() % MOD;
        f[0] = 0;
        auto g = f.exp(n);
        vector<ll> want(n);
        want[0] = 1;
        for (int k = 1; k < n; k++) {
            ll s = 0;
            for (int i = 1; i <= k; i++)
                s = (s + mul((ll)i * f.freq(i) % MOD, want[k - i])) % MOD;
            want[k] = mul(s, power(k, MOD - 2));
        }
        for (int i = 0; i < n; i++) CHECK(g.freq(i) == want[i]);
    }

    // sqrt, including a zero constant term
    for (int tc = 0; tc < 30; tc++) {
        int n = (int)(rng() % 40) + 1;
        FPS<ll> f(n);
        for (auto& x : f) x = rng() % MOD;
        f[0] = mul(rng() % MOD, rng() % MOD);
        auto r = f.sqrt(n);
        if (r.empty()) continue;
        auto sq = r * r;
        for (int i = 0; i < n; i++) CHECK(sq.freq(i) == f[i]);
    }
    {
        FPS<ll> f{0, 0, 4, 4, 1};  // (2x + x^2)^2
        auto r = f.sqrt(5);
        CHECK(r[0] == 0 && (r[1] == 2 || r[1] == MOD - 2));
        auto sq = r * r;
        for (int i = 0; i < (int)f.size(); i++) CHECK(sq.freq(i) == f[i]);
    }

    // pow, including a zero constant term
    for (int tc = 0; tc < 40; tc++) {
        int n = (int)(rng() % 30) + 1;
        FPS<ll> f(n);
        for (auto& x : f) x = rng() % MOD;
        f[0] = 1;
        ll k = rng() % 13;
        auto g = f.pow(k, n);
        FPS<ll> want{1};
        for (int i = 0; i < k; i++) want = (want * f).pre(n);
        for (int i = 0; i < n; i++) CHECK(g.freq(i) == want.freq(i));
    }
    {
        int n = 100;
        FPS<ll> f(n);
        for (auto& x : f) x = rng() % MOD;
        f[0] = 1;
        ll k = 13;
        auto g = f.pow(k, n);
        FPS<ll> want{1};
        for (int i = 0; i < k; i++) want = (want * f).pre(n);
        for (int i = 0; i < n; i++) CHECK(g.freq(i) == want.freq(i));
    }
    {
        FPS<ll> f{0, 2, 1};  // x(2 + x)
        auto g = f.pow(3, 6);
        FPS<ll> want{0, 0, 0, 8, 12, 6};
        for (int i = 0; i < 6; i++) CHECK(g.freq(i) == want[i]);

        auto g10 = f.pow(10, 12);
        FPS<ll> want10{1};
        for (int i = 0; i < 10; i++) want10 = (want10 * f).pre(12);
        for (int i = 0; i < 12; i++) CHECK(g10.freq(i) == want10.freq(i));
    }

    // zero / short series are padded to the requested length
    {
        FPS<ll> zero{0};
        auto e = zero.exp(5);
        CHECK((int)e.size() == 5 && e[0] == 1);
        FPS<ll> one{1};
        auto l = one.log(5);
        CHECK((int)l.size() == 5 && l[0] == 0);
        auto inv = one.inv(5);
        CHECK((int)inv.size() == 5 && inv[0] == 1);
        auto p = zero.pow(0, 0);
        CHECK(p.empty());
    }

    // another NTT-friendly modulus
    {
        constexpr int MOD2 = 1004535809;
        using ll2 = long long;
        vector<ll2> a(80), b(70);
        for (auto& x : a) x = rng() % MOD2;
        for (auto& x : b) x = rng() % MOD2;
        auto c = NTT<MOD2>::convolution(a, b);
        vector<ll2> d(a.size() + b.size() - 1);
        for (int i = 0; i < (int)a.size(); i++)
            for (int j = 0; j < (int)b.size(); j++)
                d[i + j] = (d[i + j] + (unsigned long long)a[i] * b[j]) % MOD2;
        CHECK(c == d);

        FPS<ll2, MOD2> f(20);
        for (auto& x : f) x = rng() % MOD2;
        f[0] = 1 + rng() % (MOD2 - 1);
        auto inv = f.inv(20);
        auto prod = f * inv;
        for (int i = 0; i < 20; i++) CHECK(prod.freq(i) == (i == 0));
    }

    cout << "OK" << endl;
    return 0;
}
