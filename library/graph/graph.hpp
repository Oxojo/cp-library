#pragma once

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
    vector<vector<Edge<T>>> g;
    
    Graph() = default;

    explicit Graph(int n) : g(n) {}

    size_t size() const { return g.size(); }

    void add(int from, int to, T cost = 1, bool direct = false) {
        g[from].emplace_back(from, to, cost);
        if (!direct) g[to].emplace_back(to, from, cost);
    }

    void read(int m, int padding = -1, bool weight = false, bool direct = false) {
        while (m--) {
            int a, b; cin >> a >> b;
            a += padding, b += padding;
            T c = T(1);
            if (weight) cin >> c;
            add(a, b, c, direct);
        }
    }

    inline vector<Edge<T>>& operator[](const int& k) { return g[k]; }
    inline const vector<Edge<T>>& operator[](const int& k) const { return g[k]; }
};

template <typename T> using Edges = vector<Edge<T>>;