#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "../graph/graph.hpp"

/**
 * @brief Tree diameter (unweighted)
 *
 * Two BFS traversals: s = farthest from 0, t = farthest from s.
 * path is the vertex sequence of one diameter.
 *
 * @complexity O(n)
 */
struct TreeDiameter {
    int n, s, t, len;
    vector<int> path;

    explicit TreeDiameter(const vector<vector<int>>& g) : n((int)g.size()) {
        assert(n > 0);

        vector<int> parent(n, -1), que(n);

        auto bfs = [&](int start) {
            fill(parent.begin(), parent.end(), -1);
            int l = 0, r = 0;
            que[r++] = start;
            parent[start] = start;
            while (l < r) {
                int v = que[l++];
                for (int nv : g[v]) {
                    if (parent[nv] != -1) continue;
                    parent[nv] = v;
                    que[r++] = nv;
                }
            }
            return que[r - 1];
        };

        s = bfs(0);
        t = bfs(s);
        for (int v = t; v != s; v = parent[v]) path.push_back(v);
        path.push_back(s);
        reverse(begin(path), end(path));

        len = (int)path.size() - 1;
    }

    // middle vertex (or the two middle vertices) of path
    pair<int, int> center() const { return {path[len / 2], path[(len + 1) / 2]}; }
};

/**
 * @brief Tree diameter (weighted, non-negative weights)
 *
 * Two DFS traversals on Graph<T> with costs.
 * len is the total weight of path.
 *
 * @complexity O(n)
 */
template <class T>
struct WeightedTreeDiameter {
    int n, s, t;
    T len{};
    vector<int> path;

    explicit WeightedTreeDiameter(const Graph<T>& g) : n((int)g.size()) {
        assert(n > 0);

        vector<int> parent;
        T dist{};

        auto farthest = [&](int start) {
            vector<char> vis(n, 0);
            vector<T> d(n, T(0));
            parent.assign(n, -1);
            vector<int> st;
            st.reserve(n);
            st.push_back(start);
            vis[start] = 1;

            int best = start;
            while (!st.empty()) {
                int v = st.back();
                st.pop_back();
                if (d[best] < d[v]) best = v;
                for (const auto& e : g[v]) {
                    int u = e;
                    if (vis[u]) continue;
                    vis[u] = 1;
                    d[u] = d[v] + e.cost;
                    parent[u] = v;
                    st.push_back(u);
                }
            }
            dist = d[best];
            return best;
        };

        s = farthest(0);
        t = farthest(s);
        len = dist;

        for (int v = t; v != -1; v = parent[v]) path.push_back(v);
        reverse(begin(path), end(path));
    }

    // middle vertex (or the two middle vertices) of path
    pair<int, int> center() const {
        int m = (int)path.size() - 1;
        return {path[m / 2], path[(m + 1) / 2]};
    }
};
