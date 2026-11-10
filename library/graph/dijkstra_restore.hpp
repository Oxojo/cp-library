#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "./graph.hpp"

// dist[v] = {distance, previous vertex on the shortest path} (-1 if unreachable)
template <typename T>
vector<pair<T, int>> dijkstra_restore(const Graph<T>& g, int s) {
    using P = pair<T, int>;
    const T inf = numeric_limits<T>::max() / 4;
    int n = (int)g.size();
    vector<P> dist(n, P{inf, -1});
    priority_queue<P, vector<P>, greater<P>> pq;
    dist[s].first = T(0);
    pq.emplace(T(0), s);
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (dist[v].first < d) continue;

        for (const auto& e : g[v]) {
            T nd = (d > inf - e.cost) ? inf : d + e.cost;
            if (nd < dist[e.to].first) {
                dist[e.to].first = nd;
                dist[e.to].second = v;
                pq.emplace(nd, e.to);
            }
        }
    }
    return dist;
}
