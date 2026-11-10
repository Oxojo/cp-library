#pragma once

#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

#include "./graph.hpp"

// dist[v] = {distance, previous vertex on the shortest path} (-1 if unreachable)
template <typename T>
std::vector<std::pair<T, int>> dijkstra_restore(const Graph<T>& g, int s) {
    using P = std::pair<T, int>;
    const T inf = std::numeric_limits<T>::max() / 4;
    int n = (int)g.size();
    std::vector<P> dist(n, P{inf, -1});
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
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
