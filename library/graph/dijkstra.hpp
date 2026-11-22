#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "./graph.hpp"

/**
 * @brief Dijkstra
 *
 * If parent is not null, it is filled with the previous vertex on a shortest
 * path (-1 for the source and unreachable vertices).
 */
template <typename T>
vector<T> dijkstra(const Graph<T>& g, int s, vector<int>* parent = nullptr) {
    using P = pair<T, int>;
    const T inf = numeric_limits<T>::max() / 4;
    int n = (int)g.size();
    vector<T> dist(n, inf);
    if (parent) parent->assign(n, -1);

    priority_queue<P, vector<P>, greater<P>> pq;
    dist[s] = T(0);
    pq.emplace(T(0), s);
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (dist[v] < d) continue;

        for (const auto& e : g[v]) {
            T nd = (d > inf - e.cost) ? inf : d + e.cost;
            if (nd < dist[e.to]) {
                dist[e.to] = nd;
                if (parent) (*parent)[e.to] = v;
                pq.emplace(nd, e.to);
            }
        }
    }
    return dist;
}
