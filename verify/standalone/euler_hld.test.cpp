// competitive-verifier: STANDALONE

#include "../../library/graph/graph.hpp"
#include "../../library/tree/euler_tour.hpp"
#include "../../library/tree/hld.hpp"

#include <random>

#define CHECK(x)                                                          \
    do {                                                                  \
        if (!(x)) {                                                       \
            cerr << "FAILED: " #x << " (line " << __LINE__ << ")" << endl; \
            return 1;                                                     \
        }                                                                 \
    } while (0)

using ll = long long;

namespace {
vector<int> brute_path(const vector<int>& parent, const vector<int>& depth, int u, int v) {
    vector<int> left, right;
    while (depth[u] > depth[v]) {
        left.push_back(u);
        u = parent[u];
    }
    while (depth[v] > depth[u]) {
        right.push_back(v);
        v = parent[v];
    }
    while (u != v) {
        left.push_back(u);
        right.push_back(v);
        u = parent[u];
        v = parent[v];
    }
    left.push_back(u);
    reverse(right.begin(), right.end());
    left.insert(left.end(), right.begin(), right.end());
    return left;
}

template <class H>
vector<int> reconstruct(const H& hld, const vector<typename H::PathSegment>& segs) {
    vector<int> res;
    for (auto& s : segs) {
        if (!s.rev) {
            for (int i = s.l; i < s.r; i++) res.push_back(hld.order[i]);
        } else {
            for (int i = s.r - 1; i >= s.l; i--) res.push_back(hld.order[i]);
        }
    }
    return res;
}
}  // namespace

int main() {
    std::mt19937 rng(777);

    // n = 1
    {
        vector<vector<int>> g(1);
        EulerTour et(g, 0);
        EulerTourLCA elca(g, 0);
        HLD hld(g, 0);
        CHECK(et.tour.size() == 1 && et.tour[0] == 0 && et.first[0] == 0);
        CHECK(elca.lca(0, 0) == 0 && elca.dist(0, 0) == 0);
        CHECK(hld.lca(0, 0) == 0 && hld.kth_ancestor(0, 0) == 0);
        CHECK(hld.path_segments(0, 0).size() == 1);
        CHECK(hld.path_segments(0, 0, true).empty());
    }

    for (int iter = 0; iter < 40; iter++) {
        int n = 2 + (int)(rng() % 18);
        vector<vector<int>> g(n);
        vector<pair<int, int>> edges;
        for (int v = 1; v < n; v++) {
            int p = (int)(rng() % v);
            g[p].push_back(v);
            g[v].push_back(p);
            edges.push_back({p, v});
        }

        // brute force root, parent, depth, preorder
        vector<int> parent(n, -1), depth(n, 0), order;
        {
            vector<int> que{0};
            parent[0] = 0;
            for (size_t i = 0; i < que.size(); i++) {
                int v = que[i];
                order.push_back(v);
                for (int u : g[v]) {
                    if (parent[u] != -1) continue;
                    parent[u] = v;
                    depth[u] = depth[v] + 1;
                    que.push_back(u);
                }
            }
        }
        auto brute_lca = [&](int u, int v) {
            while (depth[u] > depth[v]) u = parent[u];
            while (depth[v] > depth[u]) v = parent[v];
            while (u != v) {
                u = parent[u];
                v = parent[v];
            }
            return u;
        };

        // --- EulerTour ---
        EulerTour et(g, 0);
        CHECK((int)et.tour.size() == 2 * n - 1);
        CHECK(et.tour.front() == 0 && et.tour.back() == 0);
        for (int i = 0; i < (int)et.tour.size(); i++) {
            CHECK(et.tour_depth[i] == depth[et.tour[i]]);
            if (i + 1 < (int)et.tour.size()) {
                int a = et.tour[i], b = et.tour[i + 1];
                bool connected = false;
                for (int z : g[a]) connected |= (z == b);
                CHECK(connected);
            }
        }
        for (int v = 0; v < n; v++) {
            CHECK(et.first[v] >= 0 && et.tour[et.first[v]] == v);
            for (int i = 0; i < et.first[v]; i++) CHECK(et.tour[i] != v);
            // subtree interval inherited from RootedTree
            CHECK(et.out[v] - et.in[v] == et.size[v]);
            for (int i = et.in[v]; i < et.out[v]; i++) CHECK(et.is_ancestor(v, et.order[i]));
        }

        // --- EulerTourLCA ---
        EulerTourLCA elca(g, 0);
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                int w = brute_lca(u, v);
                CHECK(elca.lca(u, v) == w);
                CHECK(elca.dist(u, v) == depth[u] + depth[v] - 2 * depth[w]);
            }
        }

        // --- HLD ---
        HLD hld(g, 0);
        for (int v = 0; v < n; v++) {
            CHECK(hld.out[v] - hld.in[v] == hld.size[v]);
            CHECK(hld.order[hld.in[v]] == v);
            for (int i = hld.in[v]; i < hld.out[v]; i++) CHECK(hld.is_ancestor(v, hld.order[i]));
        }
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                auto path = brute_path(parent, depth, u, v);
                int w = brute_lca(u, v);

                CHECK(hld.lca(u, v) == w);
                CHECK(hld.dist(u, v) == (int)path.size() - 1);

                // vertex path
                auto segs = hld.path_segments(u, v);
                CHECK(reconstruct(hld, segs) == path);
                // edge path (LCA excluded)
                vector<int> edge_path;
                for (int x : path)
                    if (x != w) edge_path.push_back(x);
                CHECK(reconstruct(hld, hld.path_segments(u, v, true)) == edge_path);

                // ranges cover exactly the vertices on the path
                vector<int> covered;
                for (auto [l, r] : hld.path_ranges(u, v)) covered.push_back(r - l);
                int total = 0;
                for (int c : covered) total += c;
                CHECK(total == (int)path.size());

                // jump
                for (int k = 0; k <= (int)path.size() - 1; k++) CHECK(hld.jump(u, v, k) == path[k]);
                CHECK(hld.jump(u, v, -1) == -1);
                CHECK(hld.jump(u, v, (int)path.size()) == -1);
            }
            for (int k = 0; k <= depth[u]; k++) {
                int x = u;
                for (int i = 0; i < k; i++) x = parent[x];
                CHECK(hld.kth_ancestor(u, k) == x);
            }
            CHECK(hld.kth_ancestor(u, depth[u] + 1) == -1);
        }

        // HLD with Graph<ll> gives the same decomposition
        Graph<ll> wg(n);
        for (auto [a, b] : edges) wg.add(a, b, 1);
        HLD hld2(wg, 0);
        CHECK(hld2.depth == hld.depth);
        CHECK(hld2.lca(n - 1, 0) == 0);
        CHECK(reconstruct(hld2, hld2.path_segments(n - 1, 0)) ==
              brute_path(parent, depth, n - 1, 0));
    }

    return 0;
}
