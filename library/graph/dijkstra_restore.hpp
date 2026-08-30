#pragma once

#include "./graph.hpp"
template <typename T>
vector<pair<T, int>> dijkstra_restore(const Graph<T> &g, int s) {
    typedef pair<T, int> P;
    const T inf = numeric_limits<T>::max() / 4;
    int n = (int)g.size();
    vector<P> dist(n, P{inf, -1});
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.emplace(T(0), s);
    dist[s].first = 0;
    while (!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();
        if (dist[v].first < d) continue;

        for (const auto& nv : g[v]) {
            if (dist[nv.to].first > d + nv.cost) {
                dist[nv.to].first = d + nv.cost;
                dist[nv.to].second = v;
                pq.emplace(dist[nv.to].first, nv.to);
            }
        }
    }
    return dist;
}