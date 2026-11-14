#pragma once

#include "./scc.hpp"

/**
 * @brief 2-SAT
 *
 * Variables are 0-indexed. add_clause(i, f, j, g) adds
 * (x_i == f) OR (x_j == g).
 *
 * @complexity
 *   add_clause: O(1).
 *   satisfiable: O(n + m).
 */
struct TwoSAT {
    int n;
    vector<vector<int>> g;  // node 2*i = (x_i = false), 2*i+1 = (x_i = true)
    vector<char> answer;

    explicit TwoSAT(int n = 0) : n(n), g(2 * n) {}

    // (x_i == f) OR (x_j == h)
    void add_clause(int i, bool f, int j, bool h) {
        int a = 2 * i + (f ? 1 : 0);
        int b = 2 * j + (h ? 1 : 0);
        g[a ^ 1].push_back(b);
        g[b ^ 1].push_back(a);
    }

    // returns true and fills answer if satisfiable
    bool satisfiable() {
        SCC<vector<vector<int>>> scc(g);
        answer.assign(n, 0);
        for (int i = 0; i < n; i++) {
            if (scc.id[2 * i] == scc.id[2 * i + 1]) return false;
            // components are in topological order (source first)
            answer[i] = (scc.id[2 * i + 1] > scc.id[2 * i]);
        }
        return true;
    }
};
