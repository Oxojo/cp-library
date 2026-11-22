// competitive-verifier: STANDALONE

#include "../../library/template/template.hpp"

#define CHECK(x)                                                       \
    do {                                                               \
        if (!(x)) {                                                    \
            cerr << "FAILED: " #x << " (line " << __LINE__ << ")" << endl; \
            return 1;                                                  \
        }                                                              \
    } while (0)

int main() {
    CHECK(msb(1) == 0);
    CHECK(msb(6) == 2);
    CHECK(msb(0) == -1);
    CHECK(lsb(8) == 3);
    CHECK(lsb(0) == 64);

    CHECK(ceil(-4, 3) == -1);
    CHECK(ceil(5, 2) == 3);

    CHECK(popcnt(7) == 3);
    CHECK(pw(3) == 8);
    CHECK(msk(3) == 7);

    vl v{1, 2, 3};
    CHECK(nxp(v));
    CHECK((v == vl{1, 3, 2}));

    auto inv = mkinv(vl{5, 3, 3});
    CHECK(sz(inv) == 6);
    CHECK(inv[5] == 0);
    CHECK(inv[3] == 2);

    CHECK(mkiota(3) == (vl{0, 1, 2}));
    CHECK(mkcum(vl{1, 2, 3}) == (vl{0, 1, 3, 6}));
    CHECK(vmax(vl{3, 1, 2}) == 3 && vmin(vl{3, 1, 2}) == 1);
    CHECK(lb(vl{1, 3, 5}, 3LL) == 1 && ub(vl{1, 3, 5}, 3LL) == 2);

    return 0;
}
