#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "../structure/UnionFind.hpp"
#include "./graph.hpp"

/**
 * @brief Minimum spanning tree (Kruskal)
 *
 * edges is a flat list (Edges<T>); build it with emplace_back(u, v, w).
 *
 * @note
 *   - edges in the result are indices into the input list.
 *   - connected is false if the graph is disconnected.
 *
 * @complexity O(m log m)
 */
template <class T>
struct MstResult {
    T cost{};
    vector<int> edges;
    bool connected = true;
};

template <class T>
MstResult<T> kruskal(int n, const Edges<T>& edges) {
    vector<int> idx(edges.size());
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) { return edges[a].cost < edges[b].cost; });

    UnionFind uf(n);
    MstResult<T> res;
    for (int id : idx) {
        const auto& e = edges[id];
        if (!uf.unite(e.from, e.to)) continue;
        res.cost += e.cost;
        res.edges.push_back(id);
    }
    res.connected = ((int)res.edges.size() == max(0, n - 1));
    return res;
}
