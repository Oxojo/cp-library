#pragma once

#include "./rooted_tree.hpp"

/**
 * @brief Euler tour
 *
 * Extends RootedTree with the Euler tour of the tree.
 *
 * @note
 *   - tour has 2n-1 vertices (each edge is traversed twice, including returns).
 *   - first[v] is the first index of v in tour.
 *   - tour_depth[i] == depth[tour[i]].
 *   - subtree intervals (in/out) are inherited from RootedTree.
 *
 * @complexity Construction: O(n).
 */
template <class G = vector<vector<int>>>
struct EulerTour : RootedTree<G> {
    using Base = RootedTree<G>;

    vector<int> tour;        // vertices, length 2n-1
    vector<int> tour_depth;  // depth of tour[i]
    vector<int> first;       // first occurrence of v in tour

    explicit EulerTour(const G& g, int r = 0) : Base(g, r) {
        tour.reserve(2 * this->n - 1);
        first.assign(this->n, -1);

        vector<int> it(this->n, 0), st;
        st.reserve(this->n);
        st.push_back(this->root);

        while (!st.empty()) {
            int v = st.back();
            if (it[v] == 0) {
                first[v] = (int)tour.size();
                tour.push_back(v);
            }
            if (it[v] == (int)g[v].size()) {
                st.pop_back();
                if (!st.empty()) tour.push_back(st.back());
                continue;
            }
            int u = g[v][it[v]++];
            if (u == this->parent[v]) continue;
            st.push_back(u);
        }

        tour_depth.resize(tour.size());
        for (int i = 0; i < (int)tour.size(); i++) tour_depth[i] = this->depth[tour[i]];
    }
};

/**
 * @brief LCA by Euler tour + sparse table
 *
 * O(1) lca / dist after an O(n log n) build.
 *
 * @note Memory is O(n log n).
 *
 * @complexity
 *   Construction: O(n log n).
 *   lca / dist: O(1).
 */
template <class G = vector<vector<int>>>
struct EulerTourLCA : EulerTour<G> {
    using Base = EulerTour<G>;

    vector<vector<int>> st;  // st[k][i] = position of minimum depth in [i, i + 2^k)

    explicit EulerTourLCA(const G& g, int r = 0) : Base(g, r) {
        int m = (int)this->tour.size();
        int lg = 1;
        while ((1 << lg) <= m) lg++;

        st.assign(lg, vector<int>(m));
        iota(st[0].begin(), st[0].end(), 0);
        for (int k = 1; k < lg; k++) {
            int w = 1 << (k - 1);
            for (int i = 0; i + (1 << k) <= m; i++) {
                int a = st[k - 1][i], b = st[k - 1][i + w];
                st[k][i] = (this->tour_depth[a] <= this->tour_depth[b] ? a : b);
            }
        }
    }

    int lca(int u, int v) const {
        int l = this->first[u], r = this->first[v];
        if (l > r) swap(l, r);
        int k = 31 - __builtin_clz((unsigned)(r - l + 1));
        int a = st[k][l], b = st[k][r - (1 << k) + 1];
        return this->tour_depth[a] <= this->tour_depth[b] ? this->tour[a] : this->tour[b];
    }

    int dist(int u, int v) const {
        int w = lca(u, v);
        return this->depth[u] + this->depth[v] - 2 * this->depth[w];
    }
};
