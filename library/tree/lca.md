---
title: "Lowest common ancestor (binary lifting)"
documentation_of: ./lca.hpp
---

## 概要

根付き木の LCA をダブリングで求めます。

- `lca(u, v)` / `dist(u, v)`
- `kth_ancestor(v, k)`
- `jump(u, v, k)`: `u -> v` のパス上で `u` から `k` 個先の頂点
- `path(u, v)`: パス上の頂点列

## 使い方

```cpp
LCA lca(g, 0);
int w = lca.lca(u, v);
int d = lca.dist(u, v);
int x = lca.jump(u, v, k);
```

## 計算量

- 構築 O(n log n)
- クエリ O(log n)、`path` は O(パス長)
