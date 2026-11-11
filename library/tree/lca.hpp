#pragma once

#include "./rooted_tree.hpp"

/**
 * @brief Lowest common ancestor (binary lifting)
 *
 * Extends RootedTree with binary lifting.
 *
 * @note Vertices are 0-indexed and the root is r (default 0).
 *
 * @complexity
 *   Construction: O(n log n).
 *   lca / dist / kth_ancestor / jump: O(log n).
 *   path: O(length of the path).
 */
template <class G = vector<vector<int>>>
struct LCA : RootedTree<G> {
    using Base = RootedTree<G>;

    int log;
    vector<vector<int>> up;

    explicit LCA(const G& g, int r = 0) : Base(g, r) {
        log = 1;
        while ((1LL << log) <= this->n) log++;

        up.assign(log, vector<int>(this->n, -1));
        up[0] = this->parent;
        for (int k = 1; k < log; k++) {
            for (int v = 0; v < this->n; v++) {
                int p = up[k - 1][v];
                up[k][v] = (p == -1 ? -1 : up[k - 1][p]);
            }
        }
    }

    // k-th ancestor of v, or -1 if k > depth[v]
    int kth_ancestor(int v, int k) const {
        if (k < 0 || k > this->depth[v]) return -1;
        while (k) {
            int b = __builtin_ctz((unsigned)k);
            v = up[b][v];
            k &= k - 1;
        }
        return v;
    }

    int lca(int u, int v) const {
        if (this->is_ancestor(u, v)) return u;
        if (this->is_ancestor(v, u)) return v;

        for (int k = log - 1; k >= 0; k--) {
            int p = up[k][u];
            if (p != -1 && !this->is_ancestor(p, v)) u = p;
        }
        return up[0][u];
    }

    int dist(int u, int v) const {
        int w = lca(u, v);
        return this->depth[u] + this->depth[v] - 2 * this->depth[w];
    }

    // vertex at distance k from u on the simple path to v (0-indexed), or -1
    int jump(int u, int v, int k) const {
        int w = lca(u, v);
        int a = this->depth[u] - this->depth[w];
        int b = this->depth[v] - this->depth[w];
        if (k < 0 || k > a + b) return -1;
        if (k <= a) return kth_ancestor(u, k);
        return kth_ancestor(v, a + b - k);
    }

    // vertices on the simple path from u to v (u and v included)
    vector<int> path(int u, int v) const {
        vector<int> left, right;

        while (u != v) {
            if (this->depth[u] >= this->depth[v]) {
                left.push_back(u);
                u = up[0][u];
            } else {
                right.push_back(v);
                v = up[0][v];
            }
        }

        left.push_back(u);
        reverse(begin(right), end(right));
        left.insert(end(left), begin(right), end(right));
        return left;
    }
};
