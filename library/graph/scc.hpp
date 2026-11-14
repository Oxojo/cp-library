#pragma once

#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Strongly connected components (Kosaraju)
 *
 * Iterative implementation (safe for long paths).
 *
 * @note
 *   - groups are listed in topological order of the condensation:
 *     if there is an edge from component i to component j, then i < j.
 *   - Vertices are 0-indexed.
 *
 * @complexity O(n + m) time, O(n + m) extra space.
 */
template <class G = vector<vector<int>>>
struct SCC {
    int n;
    vector<int> id;              // component id of each vertex
    vector<vector<int>> groups;  // vertices of each component (topological order)

    explicit SCC(const G& g) : n((int)g.size()), id(n, -1) {
        vector<vector<int>> rg(n);
        for (int v = 0; v < n; v++) {
            for (const auto& e : g[v]) {
                int u = e;
                rg[u].push_back(v);
            }
        }

        // 1st pass: finishing order on the original graph
        vector<char> used(n, 0);
        vector<int> order;
        order.reserve(n);
        vector<int> it(n, 0), st;
        st.reserve(n);
        for (int s = 0; s < n; s++) {
            if (used[s]) continue;
            used[s] = 1;
            st.push_back(s);
            while (!st.empty()) {
                int v = st.back();
                if (it[v] < (int)g[v].size()) {
                    int u = g[v][it[v]++];
                    if (!used[u]) {
                        used[u] = 1;
                        st.push_back(u);
                    }
                } else {
                    order.push_back(v);
                    st.pop_back();
                }
            }
        }

        // 2nd pass: DFS on the reversed graph in reverse finishing order
        reverse(order.begin(), order.end());
        for (int s : order) {
            if (id[s] != -1) continue;
            int cid = (int)groups.size();
            groups.emplace_back();
            vector<int> st2{s};
            id[s] = cid;
            while (!st2.empty()) {
                int v = st2.back();
                st2.pop_back();
                groups[cid].push_back(v);
                for (int u : rg[v]) {
                    if (id[u] != -1) continue;
                    id[u] = cid;
                    st2.push_back(u);
                }
            }
        }
    }

    int size() const { return (int)groups.size(); }

    // true if u and v are in the same component
    bool same(int u, int v) const { return id[u] == id[v]; }
};
