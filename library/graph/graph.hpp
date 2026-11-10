#pragma once

#include <iostream>
#include <vector>

template <typename T>
struct Edge {
    int from, to;
    T cost;

    Edge() = default;
    Edge(int from, int to, T cost = T(1)) : from(from), to(to), cost(cost) {}

    operator int() const { return to; }
};

template <typename T>
struct Graph {
    std::vector<std::vector<Edge<T>>> g;

    Graph() = default;

    explicit Graph(int n) : g(n) {}

    size_t size() const { return g.size(); }

    // NOTE: directed = false (default) adds both directions, i.e. an undirected edge.
    void add(int from, int to, T cost = 1, bool directed = false) {
        g[from].emplace_back(from, to, cost);
        if (!directed) g[to].emplace_back(to, from, cost);
    }

    void read(int m, int padding = -1, bool weight = false, bool directed = false) {
        while (m--) {
            int a, b;
            std::cin >> a >> b;
            a += padding, b += padding;
            T c = T(1);
            if (weight) std::cin >> c;
            add(a, b, c, directed);
        }
    }

    inline std::vector<Edge<T>>& operator[](const int& k) { return g[k]; }
    inline const std::vector<Edge<T>>& operator[](const int& k) const { return g[k]; }
};

template <typename T> using Edges = std::vector<Edge<T>>;
