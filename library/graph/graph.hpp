#pragma once

template <typename T = ll>
struct Edge {
    ll from, to;
    T cost;
    int idx;

    Edge() = default;
    Edge(ll from, ll to, T cost = 1, int idx = -1) : from(from), to(to), cost(cost), idx(idx) {}
};

template <typename T = ll>
struct Graph {
    vv<Edge<T>> g;
    ll es;

    Graph() = default;
    explicit Graph(ll n) : g(n), es(0) {}

    size_t size() const { return g.size(); }

    void add(ll from, ll to, ll cost = 1, bool directed = false) {
        g[from].emplace_back(from, to, cost, es);
        if (!directed) g[to].emplace_back(to, from, cost, es);
        es++;
    }

    void read(ll m, ll padding = -1, bool weighted = false, bool directed = false) {
        for (ll i = 0; i < m; i++) {
            ll u, v; cin >> u >> v;
            u += padding; v += padding;
            T c = T(1);
            if (weighted) cin >> c;
            add(u, v, c, directed);
        }
    }

    inline vec<Edge<T>>& operator[](const ll &k) { return g[k]; }
};

template <typename T = ll>
using Edges = vec<Edge<T>>;
