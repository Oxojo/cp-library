#pragma once

#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Topological sort (Kahn's algorithm)
 *
 * Returns a topological order of a directed graph, or an empty vector if the
 * graph has a cycle. For an empty graph, returns an empty vector.
 *
 * @complexity O(n + m)
 */
template <class G = vector<vector<int>>>
vector<int> topological_sort(const G& g) {
    int n = (int)g.size();
    vector<int> indeg(n, 0);
    for (int v = 0; v < n; v++) {
        for (const auto& e : g[v]) {
            int u = e;
            indeg[u]++;
        }
    }

    queue<int> que;
    for (int v = 0; v < n; v++)
        if (indeg[v] == 0) que.push(v);

    vector<int> res;
    res.reserve(n);
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        res.push_back(v);
        for (const auto& e : g[v]) {
            int u = e;
            if (--indeg[u] == 0) que.push(u);
        }
    }

    if ((int)res.size() != n) return {};
    return res;
}

// true if the directed graph has no cycle
template <class G = vector<vector<int>>>
bool is_dag(const G& g) {
    return (int)topological_sort(g).size() == (int)g.size();
}
