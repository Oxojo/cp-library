#pragma once

#include <bits/stdc++.h>
using namespace std;

// Segment tree for a monoid (S, op, e).
//
//   auto op = [](ll a, ll b) { return a + b; };
//   SegmentTree seg(n, 0LL, op);              // CTAD deduces S and the functor type
//   SegmentTree<ll> seg2(n, 0LL, op);         // explicit S, op stored as std::function
//
// prod(l, r) returns the product on the half-open interval [l, r).
template <class S, class Op = function<S(S, S)>>
struct SegmentTree {
    int n = 0, sz = 1, lg = 0;
    S e{};
    Op op;
    vector<S> d;

    SegmentTree() = default;

    SegmentTree(int n_, S e_, Op op_) : n(n_), e(e_), op(op_) { build(vector<S>(n_, e_)); }

    SegmentTree(const vector<S>& v, S e_, Op op_) : n((int)v.size()), e(e_), op(op_) { build(v); }

    int size() const { return n; }

    S get(int p) const {
        assert(0 <= p && p < n);
        return d[p + sz];
    }

    void set(int p, S x) {
        assert(0 <= p && p < n);
        p += sz;
        d[p] = x;
        for (int i = 1; i <= lg; i++) update(p >> i);
    }

    // product of [l, r)
    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        S sml = e, smr = e;
        l += sz;
        r += sz;
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return d[1]; }

    // maximum r such that f(op(a[l], ..., a[r-1])) is true (f(e) must be true)
    template <class G>
    int max_right(int l, G f) const {
        assert(0 <= l && l <= n);
        if (l == n) return n;
        l += sz;
        S sm = e;
        do {
            while ((l & 1) == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < sz) {
                    l <<= 1;
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - sz;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return n;
    }

    // minimum l such that f(op(a[l], ..., a[r-1])) is true (f(e) must be true)
    template <class G>
    int min_left(int r, G f) const {
        assert(0 <= r && r <= n);
        if (r == 0) return 0;
        r += sz;
        S sm = e;
        do {
            r--;
            while (r > 1 && (r & 1)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < sz) {
                    r = 2 * r + 1;
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - sz;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

private:
    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }

    void build(const vector<S>& v) {
        assert(n >= 0);
        sz = 1;
        lg = 0;
        while (sz < n) sz <<= 1, ++lg;
        d.assign(2 * sz, e);
        for (int i = 0; i < n; i++) d[sz + i] = v[i];
        for (int i = sz - 1; i > 0; i--) update(i);
    }
};
