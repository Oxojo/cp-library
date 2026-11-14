#pragma once

#include "./rooted_tree.hpp"

/**
 * @brief Heavy-light decomposition
 *
 * Extends RootedTree with heavy-light decomposition.
 *
 * @note
 *   - in/out/order are reassigned to the HLD order (heavy child first), which
 *     is still a DFS preorder, so subtree_range / is_ancestor keep working.
 *   - pos of v is in[v]; order[i] is the vertex at position i.
 *
 * @complexity
 *   Construction: O(n).
 *   lca / dist / kth_ancestor / jump: O(log n).
 *   path_segments: O(log n) segments.
 */
template <class G = vector<vector<int>>>
struct HLD : RootedTree<G> {
    using Base = RootedTree<G>;

    struct PathSegment {
        int l, r;    // half-open interval in HLD order
        bool rev;    // true if the path traverses [l, r) from r-1 down to l
    };

    vector<int> head;

    explicit HLD(const G& g, int r = 0) : Base(g, r) {
        int n = this->n;

        vector<int> heavy(n, -1);
        for (int v = 0; v < n; v++) {
            for (int u : g[v]) {
                if (u == this->parent[v]) continue;
                if (heavy[v] == -1 || this->size[u] > this->size[heavy[v]]) heavy[v] = u;
            }
        }

        head.assign(n, -1);
        this->order.assign(n, 0);

        int t = 0;
        vector<int> st;
        st.reserve(n);
        st.push_back(this->root);
        while (!st.empty()) {
            int h = st.back();
            st.pop_back();
            for (int v = h; v != -1; v = heavy[v]) {
                head[v] = h;
                this->in[v] = t;
                this->order[t++] = v;
                for (int u : g[v]) {
                    if (u == this->parent[v] || u == heavy[v]) continue;
                    st.push_back(u);
                }
            }
        }
        for (int v = 0; v < n; v++) this->out[v] = this->in[v] + this->size[v];
    }

    int lca(int u, int v) const {
        while (head[u] != head[v]) {
            if (this->depth[head[u]] > this->depth[head[v]])
                u = this->parent[head[u]];
            else
                v = this->parent[head[v]];
        }
        return this->depth[u] < this->depth[v] ? u : v;
    }

    int dist(int u, int v) const {
        int w = lca(u, v);
        return this->depth[u] + this->depth[v] - 2 * this->depth[w];
    }

    int kth_ancestor(int v, int k) const {
        if (k < 0 || k > this->depth[v]) return -1;
        while (true) {
            int h = head[v];
            int d = this->depth[v] - this->depth[h];
            if (k <= d) return this->order[this->in[v] - k];
            k -= d + 1;
            v = this->parent[h];
        }
    }

    int jump(int u, int v, int k) const {
        int w = lca(u, v);
        int a = this->depth[u] - this->depth[w];
        int b = this->depth[v] - this->depth[w];
        if (k < 0 || k > a + b) return -1;
        if (k <= a) return kth_ancestor(u, k);
        return kth_ancestor(v, a + b - k);
    }

    /**
     * Decomposes the simple path u -> v into O(log n) segments, in path order.
     * Each segment is [l, r) in HLD order; rev tells the direction inside it.
     * When edge is true, the LCA vertex is excluded (edge path).
     */
    vector<PathSegment> path_segments(int u, int v, bool edge = false) const {
        vector<PathSegment> up, down;

        while (head[u] != head[v]) {
            if (this->depth[head[u]] > this->depth[head[v]]) {
                up.push_back({this->in[head[u]], this->in[u] + 1, true});
                u = this->parent[head[u]];
            } else {
                down.push_back({this->in[head[v]], this->in[v] + 1, false});
                v = this->parent[head[v]];
            }
        }

        if (this->depth[u] >= this->depth[v]) {
            // v is an ancestor of u: the rest of the path goes upward
            int l = this->in[v] + (edge ? 1 : 0);
            int r = this->in[u] + 1;
            if (l < r) up.push_back({l, r, true});
        } else {
            // u is an ancestor of v
            int l = this->in[u] + (edge ? 1 : 0);
            int r = this->in[v] + 1;
            if (l < r) down.push_back({l, r, false});
        }

        reverse(down.begin(), down.end());
        up.insert(up.end(), down.begin(), down.end());
        return up;
    }

    // Same as path_segments but only the intervals (for commutative monoids).
    vector<pair<int, int>> path_ranges(int u, int v, bool edge = false) const {
        auto segs = path_segments(u, v, edge);
        vector<pair<int, int>> res;
        res.reserve(segs.size());
        for (auto& s : segs) res.push_back({s.l, s.r});
        return res;
    }
};
