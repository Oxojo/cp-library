#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "./graph.hpp"

template <typename T>
vector<T> dijkstra(const Graph<T>& g, int s) {
    using P = pair<T, int>;
    const T inf = numeric_limits<T>::max() / 4;
    int n = (int)g.size();
    vector<T> dist(n, inf);
    priority_queue<P, vector<P>, greater<P>> pq;
    dist[s] = T(0);
    pq.emplace(T(0), s);
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (dist[v] < d) continue;

        for (const auto& e : g[v]) {
            // saturating add: avoids overflow when d and e.cost are both huge
            T nd = (d > inf - e.cost) ? inf : d + e.cost;
            if (nd < dist[e.to]) {
                dist[e.to] = nd;
                pq.emplace(nd, e.to);
            }
        }
    }
    return dist;
}
