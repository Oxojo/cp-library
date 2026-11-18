---
title: "Heavy-light decomposition"
documentation_of: ./hld.hpp
---

## 概要

Heavy-Light Decomposition を行い、パスを O(log n) 個の区間に分解します。

- `lca` / `dist` / `kth_ancestor` / `jump`
- `path_segments(u, v, edge = false)`: `u -> v` の区間列（`rev` 付き）
- `path_ranges(u, v)`: 可換モノイド用の区間列
- `in` / `out` は HLD 順に再割当され、部分木区間として使えます

## 使い方

```cpp
HLD hld(g, 0);
for (auto [l, r] : hld.path_ranges(u, v)) sum += seg.prod(l, r);
```

## 計算量

- 構築 O(n)
- クエリ O(log n) 区間

## 注意

- `path_segments` の各要素は `{l, r, rev}` で、`rev` は区間内を `r-1 -> l` の向きに辿ることを表します。
- `edge = true` で LCA を除外した辺パスになります。
