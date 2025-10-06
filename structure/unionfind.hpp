struct UnionFind {
    vl par, siz;
    ll cnt;
    UnionFind() = default;

    explicit UnionFind(ll n) : par(n, -1), siz(n, 1), cnt(n) {}

    ll root(ll v) {
        if (par[v] == -1) return v;
        else return par[v] = root(par[v]);
    }


    bool same(ll x, ll y) {
        x = root(x); y = root(y);
        return x == y;
    }

    bool unite(ll x, ll y) {
        x = root(x); y = root(y);
        if (x == y) return false;
        if (siz[y] > siz[x]) swap(x, y);
        siz[x] += siz[y];
        par[y] = x;
        cnt--;
        return true;
    }

    ll size(ll k) { return siz[k]; }

    ll count() { return cnt; }

    vv<ll> groups() {
        ll n = sz(par);
        vv<ll> ret(n);
        rep(i, n) {
            ret[par[i]].emplace_back(i);
        }
        ret.erase(remove_if(all(ret), [&](const vl& v){ return v.empty(); }), end(ret));
        return ret;
    }
};