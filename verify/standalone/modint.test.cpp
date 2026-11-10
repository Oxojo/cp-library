// competitive-verifier: STANDALONE

#include "../../library/math/modint.hpp"

#include <random>

#define CHECK(x)                                                          \
    do {                                                                  \
        if (!(x)) {                                                       \
            cerr << "FAILED: " #x << " (line " << __LINE__ << ")" << endl; \
            return 1;                                                     \
        }                                                                 \
    } while (0)

namespace {
constexpr long long M1 = 998244353;
constexpr long long M2 = 1000000007;

long long pow_mod(long long a, long long n, long long m) {
    long long r = 1 % m;
    a = (a % m + m) % m;
    for (; n > 0; n >>= 1) {
        if (n & 1) r = (long long)((__int128)r * a % m);
        a = (long long)((__int128)a * a % m);
    }
    return r;
}

long long norm(long long x, long long m) { return (x % m + m) % m; }
}  // namespace

int main() {
    std::mt19937_64 rng(998244353);

    CHECK(mint(-1).val() == M1 - 1);
    CHECK(mint(-5).val() == M1 - 5);
    CHECK(mint(M1).val() == 0);
    CHECK(mint(0).val() == 0);
    CHECK(modint<M2>(-1).val() == M2 - 1);

    // two different moduli can be used at the same time
    mint a = M1 - 1;
    modint<M2> b = M2 - 1;
    CHECK((a + mint(1)).val() == 0);
    CHECK((b + modint<M2>(1)).val() == 0);

    for (int iter = 0; iter < 200; iter++) {
        long long x = (long long)(rng() % (2 * M1)) - M1;
        long long y = (long long)(rng() % (2 * M1)) - M1;
        mint mx = x, my = y;

        CHECK(mx.val() == norm(x, M1));
        CHECK((mx + my).val() == norm(x + y, M1));
        CHECK((mx - my).val() == norm(x - y, M1));
        CHECK((mx * my).val() == norm((long long)((__int128)x * y % M1), M1));

        long long k = rng() % 100;
        CHECK(mx.pow(k).val() == pow_mod(x, k, M1));

        if (y % M1 != 0) {
            mint q = mx / my;
            CHECK((q * my).val() == mx.val());
        }
    }

    mint one(1);
    CHECK(one.inv().val() == 1);
    CHECK((mint(2).inv() * mint(2)).val() == 1);
    CHECK(mint(3).pow(5).val() == pow_mod(3, 5, M1));

    // I/O
    stringstream ss;
    ss << mint(12345);
    CHECK(ss.str() == "12345");
    stringstream is("67890");
    mint in;
    is >> in;
    CHECK(in.val() == 67890);

    CHECK(modint<2>(3).val() == 1);
    CHECK((modint<2>(1).inv()).val() == 1);

    return 0;
}
