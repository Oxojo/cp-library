#pragma once

#include <bits/stdc++.h>
using namespace std;

// Lazy segment tree.
//
//   S  : monoid (op, e)
//   F  : operator monoid (composition, id) acting on S via mapping(f, x)
//
//   auto op    = [](ll a, ll b) { return a + b; };
//   auto mp    = [](ll f, ll x) { return f + x; };   // S -> f(x)
//   auto comp  = [](ll f, ll g) { return f + g; };   // f(g(x))
//
// prod(l, r) is the product on [l, r), apply(l, r, f) applies f there.
template <class S, class F, class Op = function<S(S, S)>, class Mapping = function<S(F, S)>,
          class Comp = function<F(F, F)>>
struct LazySegmentTree {
    int n = 0, sz = 1, lg = 0;
    S e{};
    F id{};
    Op op;
    Mapping mapping;
    Comp comp;
    vector<S> d;
    vector<F> lz;

    LazySegmentTree() = default;

    LazySegmentTree(int n_, S e_, F id_, Op op_, Mapping mapping_, Comp comp_)
        : n(n_), e(e_), id(id_), op(op_), mapping(mapping_), comp(comp_) {
        build(vector<S>(n_, e_));
    }

    LazySegmentTree(const vector<S>& v, S e_, F id_, Op op_, Mapping mapping_, Comp comp_)
        : n((int)v.size()), e(e_), id(id_), op(op_), mapping(mapping_), comp(comp_) {
        build(v);
    }

    int size() const { return n; }

    S get(int p) {
        assert(0 <= p && p < n);
        p += sz;
        for (int i = lg; i >= 1; i--) push(p >> i);
        return d[p];
    }

    void set(int p, S x) {
        assert(0 <= p && p < n);
        p += sz;
        for (int i = lg; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= lg; i++) update(p >> i);
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return e;
        l += sz;
        r += sz;
        for (int i = lg; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        S sml = e, smr = e;
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < n);
        p += sz;
        for (int i = lg; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= lg; i++) update(p >> i);
    }

    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return;
        l += sz;
        r += sz;
        for (int i = lg; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) all_apply(l++, f);
            if (r & 1) all_apply(--r, f);
            l >>= 1;
            r >>= 1;
        }
        l = l2;
        r = r2;
        for (int i = 1; i <= lg; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <class G>
    int max_right(int l, G g) {
        assert(0 <= l && l <= n);
        assert(g(e));
        if (l == n) return n;
        l += sz;
        for (int i = lg; i >= 1; i--) push(l >> i);
        S sm = e;
        do {
            while ((l & 1) == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < sz) {
                    push(l);
                    l <<= 1;
                    if (g(op(sm, d[l]))) {
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

    template <class G>
    int min_left(int r, G g) {
        assert(0 <= r && r <= n);
        assert(g(e));
        if (r == 0) return 0;
        r += sz;
        for (int i = lg; i >= 1; i--) push((r - 1) >> i);
        S sm = e;
        do {
            r--;
            while (r > 1 && (r & 1)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < sz) {
                    push(r);
                    r = 2 * r + 1;
                    if (g(op(d[r], sm))) {
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

    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < sz) lz[k] = comp(f, lz[k]);
    }

    void push(int k) {
        if (lz[k] != id) {
            all_apply(2 * k, lz[k]);
            all_apply(2 * k + 1, lz[k]);
            lz[k] = id;
        }
    }

    void build(const vector<S>& v) {
        assert(n >= 0);
        sz = 1;
        lg = 0;
        while (sz < n) sz <<= 1, ++lg;
        d.assign(2 * sz, e);
        lz.assign(sz, id);
        for (int i = 0; i < n; i++) d[sz + i] = v[i];
        for (int i = sz - 1; i > 0; i--) update(i);
    }
};
