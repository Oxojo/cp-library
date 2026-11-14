#pragma once

#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Lowlink: bridges, articulation points, 2-edge-connected components
 *
 * Build with `Lowlink low(n); low.add_edge(u, v); low.build();`
 * Parallel edges and self-loops are handled (an edge id is used to skip only
 * the tree edge back to the parent).
 *
 * @note
 *   - bridge[e] is true for bridge edge ids.
 *   - articulation[v] is true for articulation points.
 *   - two_edge_component[v] is the 2-edge-connected component id after
 *     removing all bridges.
 *
 * @complexity O(n + m)
 */
struct Lowlink {
    int n, m = 0;
    vector<pair<int, int>> edges;             // (u, v) of each edge id
    vector<vector<pair<int, int>>> g;         // (to, edge id)
    vector<int> ord, low, parent, parent_edge;
    vector<char> bridge, articulation;
    vector<int> bridge_ids, articulation_list;
    vector<int> two_edge_component;
    int two_edge_component_count = 0;

    explicit Lowlink(int n = 0)
        : n(n), g(n), ord(n, -1), low(n), parent(n, -1), parent_edge(n, -1) {}

    int add_edge(int u, int v) {
        int id = m++;
        edges.push_back({u, v});
        g[u].push_back({v, id});
        g[v].push_back({u, id});
        return id;
    }

    void build() {
        bridge.assign(m, 0);
        articulation.assign(n, 0);
        bridge_ids.clear();
        articulation_list.clear();

        vector<int> child(n, 0);
        vector<pair<int, int>> st;  // (vertex, next adjacency index)
        int timer = 0;

        for (int s = 0; s < n; s++) {
            if (ord[s] != -1) continue;
            ord[s] = low[s] = timer++;
            st.emplace_back(s, 0);

            while (!st.empty()) {
                int v = st.back().first;
                int& idx = st.back().second;

                if (idx < (int)g[v].size()) {
                    auto [to, eid] = g[v][idx++];
                    if (eid == parent_edge[v]) continue;
                    if (ord[to] == -1) {
                        parent[to] = v;
                        parent_edge[to] = eid;
                        ord[to] = low[to] = timer++;
                        child[v]++;
                        st.emplace_back(to, 0);
                    } else {
                        low[v] = min(low[v], ord[to]);
                    }
                } else {
                    st.pop_back();
                    if (!st.empty()) {
                        int p = st.back().first;
                        low[p] = min(low[p], low[v]);
                        if (low[v] > ord[p]) bridge[parent_edge[v]] = 1;
                        if (parent[p] != -1 && low[v] >= ord[p]) articulation[p] = 1;
                    }
                }
            }
        }

        // a root is an articulation point iff it has at least two DFS children
        for (int v = 0; v < n; v++)
            if (parent[v] == -1) articulation[v] = (child[v] >= 2);

        for (int eid = 0; eid < m; eid++)
            if (bridge[eid]) bridge_ids.push_back(eid);
        for (int v = 0; v < n; v++)
            if (articulation[v]) articulation_list.push_back(v);

        // 2-edge-connected components: DFS ignoring bridges
        two_edge_component.assign(n, -1);
        two_edge_component_count = 0;
        vector<int> st2;
        for (int s = 0; s < n; s++) {
            if (two_edge_component[s] != -1) continue;
            int cid = two_edge_component_count++;
            two_edge_component[s] = cid;
            st2.push_back(s);
            while (!st2.empty()) {
                int v = st2.back();
                st2.pop_back();
                for (auto [to, eid] : g[v]) {
                    if (two_edge_component[to] != -1) continue;
                    if (bridge[eid]) continue;
                    two_edge_component[to] = cid;
                    st2.push_back(to);
                }
            }
        }
    }

    bool is_bridge(int eid) const { return bridge[eid]; }
    bool is_articulation(int v) const { return articulation[v]; }
};
