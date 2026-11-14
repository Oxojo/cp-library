#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "./graph.hpp"

/**
 * @brief BFS (unweighted shortest paths)
 *
 * Returns the distance from s (number of edges), or -1 if unreachable.
 * Weights of Graph<T> are ignored.
 *
 * @complexity O(n + m)
 */
template <class G = vector<vector<int>>>
vector<int> bfs(const G& g, int s) {
    int n = (int)g.size();
    vector<int> dist(n, -1);
    queue<int> que;
    dist[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (const auto& e : g[v]) {
            int u = e;
            if (dist[u] != -1) continue;
            dist[u] = dist[v] + 1;
            que.push(u);
        }
    }
    return dist;
}

/**
 * @brief 0-1 BFS
 *
 * Shortest paths on Graph<T> whose edge costs are 0 or 1.
 * Returns numeric_limits<T>::max() / 4 for unreachable vertices.
 *
 * @complexity O(n + m)
 */
template <class T>
vector<T> zero_one_bfs(const Graph<T>& g, int s) {
    int n = (int)g.size();
    const T INF = numeric_limits<T>::max() / 4;
    vector<T> dist(n, INF);

    deque<pair<int, T>> dq;
    dist[s] = T(0);
    dq.emplace_front(s, T(0));

    while (!dq.empty()) {
        auto [v, d] = dq.front();
        dq.pop_front();
        if (dist[v] < d) continue;

        for (const auto& e : g[v]) {
            T nd = d + e.cost;
            if (dist[e.to] <= nd) continue;
            dist[e.to] = nd;
            if (e.cost == 0)
                dq.emplace_front(e.to, nd);
            else
                dq.emplace_back(e.to, nd);
        }
    }
    return dist;
}
