---
title: "BFS (unweighted shortest paths)"
documentation_of: ./bfs.hpp
---

## 概要

- `bfs(g, s)`: 重みを無視した幅優先探索（辺数最小）
- `zero_one_bfs<T>(g, s)`: 辺コストが 0 または 1 のグラフの最短経路

## 使い方

```cpp
auto d1 = bfs(g, s);              // 到達不能は -1
auto d2 = zero_one_bfs<ll>(g, s); // 到達不能は max/4
```

## 計算量

- どちらも O(n + m)

## 注意

- `bfs` は `Graph<T>` のコストを無視します。
- `zero_one_bfs` はコストが 0/1 であることを前提とします。
