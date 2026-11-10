// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_affine_range_sum

#include "../../library/structure/LazySegmentTree.hpp"

using ll = long long;

constexpr ll MOD = 998244353;

// (sum, length)
using S = pair<ll, ll>;
// x -> a * x + b
using F = pair<ll, ll>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<S> v(n);
    for (auto& x : v) {
        ll a;
        cin >> a;
        x = S{a, 1};
    }

    auto op = [](S l, S r) { return S{(l.first + r.first) % MOD, l.second + r.second}; };
    auto mapping = [](F f, S x) { return S{(f.first * x.first + f.second * x.second) % MOD, x.second}; };
    auto comp = [](F f, F g) {
        // f(g(x))
        return F{f.first * g.first % MOD, (f.first * g.second + f.second) % MOD};
    };

    LazySegmentTree seg(v, S{0, 0}, F{1, 0}, op, mapping, comp);

    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r;
            ll b, c;
            cin >> l >> r >> b >> c;
            seg.apply(l, r, F{b, c});
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.prod(l, r).first << "\n";
        }
    }
}
