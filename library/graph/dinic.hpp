#pragma once

#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Dinic's maximum flow
 *
 * @complexity O(V^2 E) in general, much faster in practice.
 */
template <class T>
struct Dinic {
    struct Edge {
        int to, rev;
        T cap;
    };

    int n;
    vector<vector<Edge>> g;
    vector<int> level, iter;

    explicit Dinic(int n = 0) : n(n), g(n), level(n), iter(n) {}

    // returns the edge index (in g[from]) of the forward edge
    int add_edge(int from, int to, T cap) {
        int id = (int)g[from].size();
        g[from].push_back({to, (int)g[to].size(), cap});
        g[to].push_back({from, id, T(0)});
        return id;
    }

    T max_flow(int s, int t) {
        const T INF = numeric_limits<T>::max();
        T flow = T(0);
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            while (true) {
                T f = dfs(s, t, INF);
                if (f == 0) break;
                flow += f;
            }
        }
        return flow;
    }

    // vertices reachable from s in the residual graph (S-side of a min cut)
    vector<char> min_cut(int s) const {
        vector<char> vis(n, 0);
        queue<int> que;
        vis[s] = 1;
        que.push(s);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (const auto& e : g[v]) {
                if (e.cap <= 0 || vis[e.to]) continue;
                vis[e.to] = 1;
                que.push(e.to);
            }
        }
        return vis;
    }

private:
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (const auto& e : g[v]) {
                if (e.cap <= 0 || level[e.to] != -1) continue;
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
        return level[t] != -1;
    }

    T dfs(int v, int t, T f) {
        if (v == t) return f;
        for (int& i = iter[v]; i < (int)g[v].size(); i++) {
            Edge& e = g[v][i];
            if (e.cap <= 0 || level[e.to] != level[v] + 1) continue;
            T d = dfs(e.to, t, min(f, e.cap));
            if (d == 0) continue;
            e.cap -= d;
            g[e.to][e.rev].cap += d;
            return d;
        }
        return 0;
    }
};
