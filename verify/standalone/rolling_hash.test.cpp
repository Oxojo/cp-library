// competitive-verifier: STANDALONE

#include "../../library/string/rolling_hash.hpp"

#include <random>

#define CHECK(x)                                                          \
    do {                                                                  \
        if (!(x)) {                                                       \
            cerr << "FAILED: " #x << " (line " << __LINE__ << ")" << endl; \
            return 1;                                                     \
        }                                                                 \
    } while (0)

int main() {
    using ull = unsigned long long;
    mt19937_64 rng(20261122);
    for (int tc = 0; tc < 100; ++tc) {
        int n = 1 + (int)(rng() % 60);
        string s(n, 'a');
        for (char& c : s) c = char('a' + rng() % 5);

        RollingHash rh;
        rh.build(s);
        vector<ull> h(n + 1), pw(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            h[i + 1] = RollingHash::add(
                RollingHash::mul(h[i], rh.base), (unsigned char)s[i]);
            pw[i + 1] = RollingHash::mul(pw[i], rh.base);
        }
        for (int l = 0; l <= n; ++l)
            for (int r = l; r <= n; ++r)
                CHECK(rh.get(l, r) ==
                      RollingHash::sub(h[r],
                                       RollingHash::mul(h[l], pw[r - l])));
        for (int q = 0; q < 30; ++q) {
            int a = (int)(rng() % n);
            int b = (int)(rng() % n);
            int lim = n - max(a, b);
            int want = 0;
            while (want < lim && s[a + want] == s[b + want]) ++want;
            CHECK(rh.lcp(a, b, lim) == want);
        }
    }
    cout << "OK" << endl;
    return 0;
}
