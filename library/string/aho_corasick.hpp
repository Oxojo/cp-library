#pragma once

#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Aho-Corasick automaton
 *
 * Builds a trie of lowercase English patterns and its failure links.
 * Call add() for each pattern, then build().
 */
struct AhoCorasick {
    struct Node {
        array<int, 26> next;
        int link = 0;
        int parent = -1;
        Node() { next.fill(-1); }
    };

    vector<Node> nodes;
    vector<int> ends;
    vector<int> order;

    AhoCorasick() { nodes.emplace_back(); }

    int add(const string& s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (nodes[v].next[c] == -1) {
                nodes[v].next[c] = (int)nodes.size();
                nodes.emplace_back();
                nodes.back().parent = v;
            }
            v = nodes[v].next[c];
        }
        ends.push_back(v);
        return v;
    }

    void build() {
        order.clear();
        queue<int> q;
        for (int c = 0; c < 26; ++c) {
            int u = nodes[0].next[c];
            if (u != -1) {
                nodes[u].link = 0;
                q.push(u);
            } else {
                nodes[0].next[c] = 0;
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            order.push_back(v);
            for (int c = 0; c < 26; ++c) {
                int u = nodes[v].next[c];
                if (u != -1) {
                    nodes[u].link = nodes[nodes[v].link].next[c];
                    q.push(u);
                } else {
                    nodes[v].next[c] = nodes[nodes[v].link].next[c];
                }
            }
        }
    }

    // Number of occurrences of each added pattern.
    vector<int> match_count(const string& text) const {
        vector<int> cnt(nodes.size());
        int v = 0;
        for (char ch : text) {
            v = nodes[v].next[ch - 'a'];
            ++cnt[v];
        }
        for (int i = (int)order.size() - 1; i >= 0; --i) {
            int u = order[i];
            cnt[nodes[u].link] += cnt[u];
        }
        vector<int> res(ends.size());
        for (int i = 0; i < (int)ends.size(); ++i) res[i] = cnt[ends[i]];
        return res;
    }
};
