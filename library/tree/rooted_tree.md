---
title: "Rooted tree"
documentation_of: ./rooted_tree.hpp
---

## 概要

反復 DFS で根付き木の基本情報を構築します。

- `parent` / `depth` / `size` / `order` / `in` / `out`
- `subtree_range(v)`（`[in, out)`）、`is_ancestor(u, v)`、`is_leaf(v)`

## 使い方

```cpp
RootedTree tr(g, 0);     // vector<vector<int>> でも Graph<T> でも可
auto [l, r] = tr.subtree_range(v);
bool anc = tr.is_ancestor(u, v);
```

## 計算量

- 構築 O(n)

## 注意

- 連結な無向木を前提とします。
- 部分木の頂点は `order[in[v] ... out[v]-1]` です。
