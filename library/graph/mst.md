---
title: "Minimum spanning tree (Kruskal)"
documentation_of: ./mst.hpp
---

## 概要

Kruskal 法で最小全域木を求めます。辺リスト `Edges<T>` を渡します。

## 使い方

```cpp
Edges<ll> es;
es.emplace_back(u, v, cost);
auto res = kruskal(n, es);

// res.cost        : 最小全域木のコスト
// res.edges       : 入力辺のインデックス
// res.connected   : 連結かどうか
```

## 計算量

- O(m log m)

## 注意

- 辺のインデックスは入力リストの順序です。
- 非連結なら `connected == false` です。
