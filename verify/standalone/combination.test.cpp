// competitive-verifier: STANDALONE

#include "../../library/math/combination.hpp"

#define CHECK(x)                                                          \
    do {                                                                  \
        if (!(x)) {                                                       \
            cerr << "FAILED: " #x << " (line " << __LINE__ << ")" << endl; \
            return 1;                                                     \
        }                                                                 \
    } while (0)

namespace {
// Pascal's triangle modulo mod
long long pascal(int n, int k, long long mod) {
    if (k < 0 || n < k) return 0;
    vector<vector<long long>> c(n + 1, vector<long long>(n + 1, 0));
    c[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
    }
    return c[n][k];
}
}  // namespace

int main() {
    // n must stay below mod for the factorial precomputation to be valid
    for (long long mod : {998244353LL, 1000000007LL, 2LL, 3LL}) {
        int N = (int)min<long long>(60, mod - 1);
        Combination comb(N, mod);
        for (int n = 0; n <= N; n++) {
            for (int k = 0; k <= n + 3; k++) {
                CHECK(comb.C(n, k) == pascal(n, k, mod));
            }
            long long f = 1;
            for (int k = 0; k <= n; k++) {
                if (k > 0) f = f * k % mod;
                CHECK(comb.P(n, k) == comb.C(n, k) * f % mod);
            }
        }
        // nHk = (n+k-1)Ck
        for (int n = 1; n <= N; n++) {
            for (int k = 0; n + k - 1 <= N; k++) {
                CHECK(comb.H(n, k) == comb.C(n + k - 1, k));
            }
        }
        CHECK(comb.H(0, 0) == 1 % mod);
        CHECK(comb.H(0, 1) == 0);
    }
    return 0;
}
