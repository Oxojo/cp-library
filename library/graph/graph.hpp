#pragma once

#include "../template/template.hpp"

template <typename T = ll>
struct Edge {
    ll from, to;
    T cost;
    
    Edge() = default;

    Edge(ll from, ll to, T cost = T(1)) : from(from), to(to), cost(cost) {}
};

template <typename T = ll>
struct Graph {
    vv<Edge<T>> g;
    
    Graph() = default;

    explicit Graph(ll n) : g(n) {}

    size_t size() const { return g.size(); }

    void add(ll from, ll to, T cost = 1, bool direct = false) {
        g[from].emplace_back(from, to, cost);
        if (direct) g[to].emplace_back(to, from, cost);
    }

    void read(ll m, ll padding = -1, bool weigtht = false, bool direct = false) {
        rep(i, m) {
            ll a, b; cin >> a >> b;
            a += padding, b += padding;
            T c = T(1);
            if (weight) cin >> c;
            add(from, to, cost, direct);
        }
    }

    inline vec<Edge<T>>& operator[](const ll& k) { return g[k]; }

    inline const vec<Edge<T>>& operator[](const ll& k) { return g[k]; }
};

template<typename T = ll> using Edges = vec<Edge<T>>;