template <typename T = ll>
struct FenwickTree {
    ll n;
    vec<T> data;

    FenwickTree() = default;
    FenwickTree(ll size) { init(size); }
    FenwickTree(vec<T> &a) {
        init(sz(a));
        rep(i, sz(a)) add(i, a[i]);
    }
    
    void init(ll size) {
        n = size + 2;
        data.assign(n + 1, {});
    }

    // sum of [0, k]
    T sum(ll k) const {
        if (k < 0) return T{};
        T ret{};
        for (++k; k > 0; k -= k & -k) ret += data[k];
        return ret;
    }

    // sum of [l, r]
    inline T sum(ll l, ll r) const { return sum(r) - sum(l - 1); }

    // value of k
    inline T operator[](ll k) const { return sum(k) - sum(k - 1); }

    // data[k] += x
    void add(ll k, T x) {
        for (++k; k < n; k += k & -k) data[k] += x;
    }

    // data[l, ..., r] += x
    void imos(ll l, ll r, T x) {
        add(l, x);
        add(r + 1, -x);
    }
    
    // min i s.t. sum(i) >= w
    ll lower_bound(T w) {
        if (w <= 0) return 0;
        ll x = 0;
        for (ll k = 1 << __lg(n); k; k >>= 1) {
            if (x + k <= n - 1 && data[x + k] < w) {
                w -= data[x + k];
                x += k;
            }
        }
        return x;
    }

    // min i s.t. sum(i) > w
    ll upper_bound(T w) {
        if (w < 0) return 0;
        ll x = 0;
        for (ll k = 1 << __lg(n); k; k >>= 1) {
            if (x + k <= n - 1 && data[x + k] <= w) {
                w -= data[x + k];
                x += k;
            }
        }
        return x;
    }
};