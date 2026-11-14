#pragma once

#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Bipartite matching (Hopcroft-Karp)
 *
 * Left vertices are 0 .. L-1 and right vertices are 0 .. R-1.
 * The augmenting path search is iterative (no deep recursion).
 *
 * @note
 *   - match_left[u] is the matched right vertex, or -1.
 *   - match_right[v] is the matched left vertex, or -1.
 *
 * @complexity O(E sqrt(V))
 */
struct BipartiteMatching {
    int L, R;
    vector<vector<int>> g;
    vector<int> match_left, match_right;

    explicit BipartiteMatching(int L, int R)
        : L(L), R(R), g(L), match_left(L, -1), match_right(R, -1) {}

    void add_edge(int u, int v) { g[u].push_back(v); }

    int max_matching() {
        int res = 0;
        while (bfs()) {
            iter.assign(L, 0);
            for (int u = 0; u < L; u++)
                if (match_left[u] == -1 && dfs(u)) res++;
        }
        return res;
    }

private:
    vector<int> dist, iter;

    bool bfs() {
        queue<int> que;
        dist.assign(L, -1);
        for (int u = 0; u < L; u++) {
            if (match_left[u] != -1) continue;
            dist[u] = 0;
            que.push(u);
        }

        bool found = false;
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int v : g[u]) {
                int w = match_right[v];
                if (w == -1) {
                    found = true;
                } else if (dist[w] == -1) {
                    dist[w] = dist[u] + 1;
                    que.push(w);
                }
            }
        }
        return found;
    }

    // iterative DFS on the layered graph (u -> v -> match_right[v])
    bool dfs(int start) {
        vector<int> su{start};
        vector<int> sv;  // right vertex chosen from su[i]

        while (!su.empty()) {
            int u = su.back();
            bool advanced = false;

            while (iter[u] < (int)g[u].size()) {
                int v = g[u][iter[u]++];
                if (match_right[v] == -1) {
                    sv.push_back(v);
                    for (int i = 0; i < (int)su.size(); i++) {
                        match_left[su[i]] = sv[i];
                        match_right[sv[i]] = su[i];
                    }
                    return true;
                }
                int w = match_right[v];
                if (dist[w] == dist[u] + 1) {
                    sv.push_back(v);
                    su.push_back(w);
                    advanced = true;
                    break;
                }
            }

            if (advanced) continue;

            dist[u] = -1;
            su.pop_back();
            if (!sv.empty()) sv.pop_back();
        }
        return false;
    }
};
