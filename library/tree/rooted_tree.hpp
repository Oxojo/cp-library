#pragma once

#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Rooted tree
 *
 * Builds a rooted tree with an iterative DFS (no recursion).
 *
 * @note
 *   - The input must be a connected, undirected tree.
 *   - Vertices are 0-indexed; the root has parent -1 and depth 0.
 *   - Vertices of the subtree of v are order[in[v] ... out[v]-1],
 *     and out[v] - in[v] == size[v].
 *   - A vertex is an ancestor of itself.
 *
 * @complexity
 *   Construction: O(n) time, O(n) extra space.
 *   subtree_range / is_ancestor: O(1).
 */
template <class G = vector<vector<int>>>
struct RootedTree {
    int n, root;
    vector<int> parent, depth, size, order, in, out;

    explicit RootedTree(const G& g, int r = 0)
        : n((int)g.size()), root(r), parent(n, -1), depth(n), size(n, 1), in(n), out(n) {
        assert(n > 0 && 0 <= root && root < n);
        order.reserve(n);

        vector<int> it(n, 0), st;
        st.reserve(n);
        st.push_back(root);

        while (!st.empty()) {
            int v = st.back();
            if (it[v] == 0) {
                in[v] = (int)order.size();
                order.push_back(v);
            }
            if (it[v] == (int)g[v].size()) {
                out[v] = (int)order.size();
                st.pop_back();
                if (parent[v] != -1) size[parent[v]] += size[v];
                continue;
            }
            int u = g[v][it[v]++];
            if (u == parent[v]) continue;
            parent[u] = v;
            depth[u] = depth[v] + 1;
            st.push_back(u);
        }
        assert((int)order.size() == n);
    }

    // [in[v], out[v])
    pair<int, int> subtree_range(int v) const { return {in[v], out[v]}; }

    bool is_ancestor(int u, int v) const { return in[u] <= in[v] && in[v] < out[u]; }

    bool is_leaf(int v) const { return out[v] - in[v] == 1; }
};
