// competitive-verifier: STANDALONE

#include "../../library/fps/fps.hpp"

#include <random>

#define CHECK(x)                                                       \
    do {                                                               \
        if (!(x)) {                                                    \
            cerr << "FAILED: " #x << " (line " << __LINE__ << ")" << endl; \
            return 1;                                                  \
        }                                                              \
    } while (0)

namespace {
constexpr ll MOD = 998244353;
std::mt19937_64 rng(20261111);

ll mul(ll a, ll b) { return modmul(a, b, MOD); }

// coefficient of x^idx in a(x + c)
ll shift_naive(const FPS<ll>& a, ll c, int idx) {
    ll res = 0;
    ll comb = 1;  // C(idx, idx)
    for (int k = idx; k < (int)a.size(); k++) {
        res = (res + mul(mul(a[k], comb), modpow(c, k - idx, MOD))) % MOD;
        // C(k+1, idx) = C(k, idx) * (k + 1) / (k + 1 - idx)
        comb = mul(mul(comb, k + 1), modinv(k + 1 - idx, MOD));
    }
    return res;
}
}  // namespace

int main() {
    for (int iter = 0; iter < 30; iter++) {
        int n = 1 + (int)(rng() % 24);
        FPS<ll> a(n), b(n);
        for (auto& x : a) x = rng() % MOD;
        for (auto& x : b) x = rng() % MOD;

        FPS<ll> s = a + b, d = a - b;
        for (int i = 0; i < n; i++) {
            CHECK(s[i] == (a[i] + b[i]) % MOD);
            CHECK(d[i] == (a[i] - b[i] + MOD) % MOD);
        }

        FPS<ll> dot = a.dot(b);
        for (int i = 0; i < n; i++) CHECK(dot[i] == mul(a[i], b[i]));

        for (int t = 0; t < 3; t++) {
            ll x = rng() % MOD;
            ll want = 0, w = 1;
            for (auto v : a) {
                want = (want + mul(w, v)) % MOD;
                w = mul(w, x);
            }
            CHECK(a(x) == want);
        }

        ll c = rng() % MOD;
        FPS<ll> sh = a.shift(c);
        for (int i = 0; i < n; i++) CHECK(sh[i] == shift_naive(a, c, i));

        FPS<ll> divisor{1, 1};
        auto qr = a.div_mod(divisor);
        FPS<ll> rec = qr.first * divisor + qr.second;
        for (int i = 0; i < n; i++) CHECK(rec[i] == a[i]);
        for (int i = 1; i < (int)qr.second.size(); i++) CHECK(qr.second[i] == 0);

        FPS<ll> l2 = a << 2, r2 = a >> 1;
        CHECK((int)l2.size() == n + 2);
        for (int i = 0; i < n; i++) CHECK(l2[i + 2] == a[i]);
        for (int i = 0; i + 1 < n; i++) CHECK(r2[i] == a[i + 1]);
    }
    return 0;
}
