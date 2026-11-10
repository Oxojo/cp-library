// competitive-verifier: STANDALONE

#include "../../library/structure/LazySegmentTree.hpp"

using ll = long long;
#include "../../library/structure/SegmentTree.hpp"

using ll = long long;

#include <random>

#define CHECK(x)                                                          \
    do {                                                                  \
        if (!(x)) {                                                       \
            cerr << "FAILED: " #x << " (line " << __LINE__ << ")" << endl; \
            return 1;                                                     \
        }                                                                 \
    } while (0)

int main() {
    std::mt19937_64 rng(314159);

    // --- SegmentTree: non-commutative monoid (string concatenation) ---
    {
        int n = 20;
        vector<string> v(n);
        for (int i = 0; i < n; i++) v[i] = string(1, char('a' + i % 26));
        auto op = [](const string& a, const string& b) { return a + b; };
        SegmentTree seg(v, string(""), op);

        for (int l = 0; l <= n; l++) {
            for (int r = l; r <= n; r++) {
                string want;
                for (int i = l; i < r; i++) want += v[i];
                CHECK(seg.prod(l, r) == want);
            }
        }
        CHECK(seg.all_prod().size() == (size_t)n);

        v[3] = "X";
        seg.set(3, "X");
        CHECK(seg.get(3) == "X");
        CHECK(seg.prod(0, 5) == v[0] + v[1] + v[2] + v[3] + v[4]);

        // max_right: max r such that |prod(l, r)| <= 4
        auto le4 = [](const string& s) { return s.size() <= 4; };
        for (int l = 0; l <= n; l++) {
            int want = min(n, l + 4);
            CHECK(seg.max_right(l, le4) == want);
        }
        // min_left: min l such that |prod(l, r)| <= 4
        for (int r = 0; r <= n; r++) {
            int want = max(0, r - 4);
            CHECK(seg.min_left(r, le4) == want);
        }
    }

    // --- LazySegmentTree: range add, range sum ---
    {
        using S = pair<ll, ll>;  // (sum, length)
        using F = ll;            // add
        int n = 28;
        vector<S> init(n);
        vector<ll> brute(n);
        for (int i = 0; i < n; i++) {
            brute[i] = (ll)(rng() % 20);
            init[i] = S{brute[i], 1};
        }
        auto op = [](S a, S b) { return S{a.first + b.first, a.second + b.second}; };
        auto mp = [](F f, S x) { return S{x.first + f * x.second, x.second}; };
        auto comp = [](F f, F g) { return f + g; };
        LazySegmentTree seg(init, S{0, 0}, F{0}, op, mp, comp);

        for (int iter = 0; iter < 300; iter++) {
            int l = (int)(rng() % (n + 1));
            int r = (int)(rng() % (n + 1));
            if (l > r) swap(l, r);
            int type = (int)(rng() % 4);
            if (type == 0) {
                ll x = (ll)(rng() % 20);
                seg.apply(l, r, x);
                for (int i = l; i < r; i++) brute[i] += x;
            } else if (type == 1) {
                ll want = 0;
                for (int i = l; i < r; i++) want += brute[i];
                CHECK(seg.prod(l, r).first == want);
            } else if (type == 2) {
                if (l < n) {
                    ll x = (ll)(rng() % 20);
                    seg.set(l, S{x, 1});
                    brute[l] = x;
                    CHECK(seg.get(l).first == x);
                }
            } else {
                // max_right with sum <= limit
                ll limit = (ll)(rng() % 200);
                int want = l;
                ll s = 0;
                while (want < n && s + brute[want] <= limit) s += brute[want++];
                auto le = [limit](S x) { return x.first <= limit; };
                CHECK(seg.max_right(l, le) == want);

                // min_left
                want = r;
                s = 0;
                while (want > 0 && s + brute[want - 1] <= limit) s += brute[--want];
                CHECK(seg.min_left(r, le) == want);
            }
        }

        for (int i = 0; i < n; i++) CHECK(seg.get(i).first == brute[i]);
    }

    return 0;
}
