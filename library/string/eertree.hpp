#pragma once

#include <bits/stdc++.h>
using namespace std;

/// @brief Eertree (palindromic tree)
///
/// Nodes 0 and 1 are the EVEN and ODD roots.  New palindromes are numbered
/// 2, 3, ... in order of first occurrence.
struct Eertree {
    vector<int> len, link, parent, endpos;
    vector<array<int, 26>> next;
    vector<int> prefix_last;
    string s;
    int last;

    Eertree() { clear(); }

    void clear() {
        len = {0, -1};
        link = {1, 1};
        parent = {-1, -1};
        endpos = {-1, -1};
        next.assign(2, {});
        next[0].fill(-1);
        next[1].fill(-1);
        prefix_last.clear();
        s.clear();
        last = 0;
    }

    int size() const { return (int)len.size() - 2; }

    void add(char ch) {
        int i = (int)s.size();
        s.push_back(ch);
        int c = ch - 'a';

        int cur = last;
        while (true) {
            int p = i - len[cur] - 1;
            if (p >= 0 && s[p] == ch) break;
            cur = link[cur];
        }

        if (next[cur][c] != -1) {
            last = next[cur][c];
            prefix_last.push_back(last);
            return;
        }

        int now = (int)len.size();
        len.push_back(len[cur] + 2);
        parent.push_back(cur);
        endpos.push_back(i);
        next.push_back({});
        next[now].fill(-1);

        if (len[now] == 1) {
            link.push_back(0);
        } else {
            int p = link[cur];
            while (true) {
                int q = i - len[p] - 1;
                if (q >= 0 && s[q] == ch) break;
                p = link[p];
            }
            assert(next[p][c] != -1);
            link.push_back(next[p][c]);
        }

        next[cur][c] = now;
        last = now;
        prefix_last.push_back(last);
    }

    void build(const string& str) {
        clear();
        for (char ch : str) add(ch);
    }
};
