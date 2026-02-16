#pragma once

#include "../template/template.hpp"
#include "../graph/graph.hpp"

template <typename T = ll>
struct scc : Graph<T> {
public:
    using Graph<T>::Graph;
    using Graph<T>::g;
    vl cmp;
    Graph<T> dag;
    vv<ll> group;

    void build() {
        rg = Graph<T>(sz(g));
        rep(i, sz(g)) fore(e, g[i]) {
            rg.add(e.to, e.from, e.cost, 1);
        }
        cmp.assign(sz(g), -1);
        use.assign(sz(g), 0);
        rep(i,sz(g)) dfs(i);
        rev(ord);
        ll ptr = 0;
        for (ll i : ord) {
            if (cmp[i] == -1) rdfs(i, ptr), ptr++;
        }
        dag = Graph<T>(ptr);
        rep(i, sz(g)) {
            fore(e, g[i]) {
                ll x = cmp[e.from], y = cmp[e.to];
                if (x == y) continue;
                dag.add(x, y, e.cost, 1);
            }
        }
        group.resize(ptr);
        rep(i, sz(g)) group[cmp[i]].eb(i);
    }

    ll operator[](ll k) const { return cmp[k]; }

private:
    vl ord, use;
    Graph<T> rg;

    void dfs(ll idx) {
        if (exchange(use[idx], true)) return;
        fore(to, g[idx]) dfs(to);
        ord.pb(idx);
    }

    void rdfs(ll idx, ll cnt) {
        if (cmp[idx] != -1) return;
        cmp[idx] = cnt;
        fore(to, rg.g[idx]) rdfs(to, cnt);
    }
};