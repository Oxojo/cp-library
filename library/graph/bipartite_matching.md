---
title: "Bipartite matching (Hopcroft-Karp)"
documentation_of: ./bipartite_matching.hpp
---

## 概要

Hopcroft-Karp 法で二部グラフの最大マッチングを求めます。
augmenting path の探索は反復実装です。

## 使い方

```cpp
BipartiteMatching bm(L, R);
bm.add_edge(u, v);

int sz = bm.max_matching();
int v = bm.match_left[u];   // 未マッチなら -1
```

## 計算量

- O(E sqrt(V))

## 注意

- 左側は `0 .. L-1`、右側は `0 .. R-1` です。
