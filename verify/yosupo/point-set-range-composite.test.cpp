// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_set_range_composite

#include "../../library/structure/SegmentTree.hpp"

using ll = long long;

constexpr ll MOD = 998244353;

struct Affine {
    ll a, b;  // x -> a * x + b
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<Affine> v(n);
    for (auto& f : v) cin >> f.a >> f.b;

    auto op = [](Affine l, Affine r) {
        // apply l first, then r
        return Affine{l.a * r.a % MOD, (l.b * r.a + r.b) % MOD};
    };
    SegmentTree seg(v, Affine{1, 0}, op);

    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int p;
            ll c, d;
            cin >> p >> c >> d;
            seg.set(p, Affine{c, d});
        } else {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            Affine f = seg.prod(l, r);
            cout << (f.a * x + f.b) % MOD << "\n";
        }
    }
}
