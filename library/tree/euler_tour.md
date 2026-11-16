---
title: "Euler tour"
documentation_of: ./euler_tour.hpp
---

## 概要

Euler tour と、それを使った O(1) LCA を提供します。

- `EulerTour`: `tour`（長さ `2n-1`）、`tour_depth`、`first`
- `EulerTourLCA`: Sparse Table による RMQ で `lca` / `dist` が O(1)

## 使い方

```cpp
EulerTourLCA lca(g, 0);
int w = lca.lca(u, v);
int d = lca.dist(u, v);
```

## 計算量

- 構築 O(n log n)
- `lca` / `dist` O(1)
- メモリ O(n log n)

## 注意

- ダブリング版よりクエリは速いが、メモリ使用量は大きくなります。
