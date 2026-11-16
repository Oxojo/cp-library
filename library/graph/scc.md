---
title: "Strongly connected components (Kosaraju)"
documentation_of: ./scc.hpp
---

## 概要

Kosaraju 法（反復 DFS）で強連結成分分解します。
`groups` は縮約グラフのトポロジカル順（辺 `u -> v` なら `id[u] <= id[v]`）です。

## 使い方

```cpp
SCC scc(g);          // vector<vector<int>> でも Graph<T> でも可
int c = scc.id[v];   // 成分番号
bool same = scc.same(u, v);
for (auto& gr : scc.groups) { /* ... */ }
```

## 計算量

- O(n + m)

## 注意

- 再帰を使わないため、長いパスでもスタックオーバーフローしません。
- 逆グラフを保持するためメモリは O(n + m) です。
