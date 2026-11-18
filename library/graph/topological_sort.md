---
title: "Topological sort (Kahn's algorithm)"
documentation_of: ./topological_sort.hpp
---

## 概要

Kahn 法で有向グラフをトポロジカルソートします。

## 使い方

```cpp
auto order = topological_sort(g);  // 閉路があれば空
bool dag = is_dag(g);
```

## 計算量

- O(n + m)

## 注意

- 有向グラフ専用です（無向グラフに使うと次数の計算が壊れます）。
- 空グラフでは空の `vector` を返します。
