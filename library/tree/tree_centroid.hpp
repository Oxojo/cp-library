#pragma once

#include "./rooted_tree.hpp"

/**
 * @brief Tree centroids
 *
 * A vertex v is a centroid if every connected component after removing v has
 * at most n/2 vertices. A tree has one or two centroids.
 *
 * @complexity O(n)
 */
template <class G = vector<vector<int>>>
struct TreeCentroid {
    vector<int> centroids;

    explicit TreeCentroid(const G& g) {
        int n = (int)g.size();
        assert(n > 0);

        RootedTree<G> tr(g, 0);

        for (int v = 0; v < n; v++) {
            int mx = n - tr.size[v];
            for (int u : g[v]) {
                if (u == tr.parent[v]) continue;
                mx = max(mx, tr.size[u]);
            }
            if (mx * 2 <= n) centroids.push_back(v);
        }
    }
};
