#pragma once

#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Edge {
    int from, to;
    T cost;

    Edge() = default;
    Edge(int from, int to, T cost = T(1)) : from(from), to(to), cost(cost) {}

    operator int() const { return to; }
};

/**
 * @brief Graph (adjacency list)
 *
 * add() is directed.  Use add_undirected() for an undirected edge.
 */
template <typename T>
struct Graph {
    vector<vector<Edge<T>>> g;

    Graph() = default;
    explicit Graph(int n) : g(n) {}

    size_t size() const { return g.size(); }

    void add(int from, int to, T cost = T(1)) {
        g[from].emplace_back(from, to, cost);
    }

    void add_undirected(int u, int v, T cost = T(1)) {
        add(u, v, cost);
        add(v, u, cost);
    }

    inline vector<Edge<T>>& operator[](const int& k) { return g[k]; }
    inline const vector<Edge<T>>& operator[](const int& k) const { return g[k]; }
};

template <typename T> using Edges = vector<Edge<T>>;
