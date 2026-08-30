#pragma once

#include "./graph.hpp"
template <typename T>
vector<T> dijkstra(Graph<T> &g, int s) {
    typedef pair<T, int> P;
    const T inf = numeric_limits<T>::max() / 4;
    int n = (int)g.size();
    vector<T> dist(n, inf);
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.emplace(T(0), s);
    dist[s] = 0;
    while (!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();
        if (dist[v] < d) continue;

        for (const auto& nv : g[v]) {
            if (dist[nv.to] > d + nv.cost) {
                dist[nv.to] = d + nv.cost;
                pq.emplace(dist[nv.to], nv.to);
            }
        }
    }
    return dist;
}