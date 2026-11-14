#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "./graph.hpp"

/**
 * @brief Bellman-Ford
 *
 * Single source shortest paths with negative edges.
 *
 * @note
 *   - edges are a flat list (Edges<T>); build it with emplace_back(u, v, w).
 *   - negative_cycle is true if a negative cycle reachable from s exists.
 *   - unreachable vertices have numeric_limits<T>::max() / 4.
 *
 * @complexity O(n * m)
 */
template <class T>
struct BellmanFordResult {
    vector<T> dist;
    bool negative_cycle = false;
};

template <class T>
BellmanFordResult<T> bellman_ford(int n, const Edges<T>& edges, int s) {
    const T INF = numeric_limits<T>::max() / 4;
    BellmanFordResult<T> res;
    res.dist.assign(n, INF);
    res.dist[s] = T(0);

    for (int iter = 0; iter < n; iter++) {
        bool updated = false;
        for (const auto& e : edges) {
            if (res.dist[e.from] == INF) continue;
            if (e.cost >= 0 && res.dist[e.from] > INF - e.cost) continue;
            T nd = res.dist[e.from] + e.cost;
            if (nd < res.dist[e.to]) {
                res.dist[e.to] = nd;
                updated = true;
            }
        }
        if (!updated) break;
        if (iter == n - 1) res.negative_cycle = true;
    }
    return res;
}
