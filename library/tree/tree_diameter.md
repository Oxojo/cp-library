---
title: "Tree diameter"
documentation_of: ./tree_diameter.hpp
---

## 概要

木の直径を求めます。

- `TreeDiameter`: 無向・非重み付き（`vector<vector<int>>`、BFS 2 回）
- `WeightedTreeDiameter<T>`: 非負重み付き（`Graph<T>`、DFS 2 回）

どちらも `s` / `t` / `len` / `path` / `center()` を持ちます。

## 使い方

```cpp
TreeDiameter d(g);
cout << d.len << " " << d.path.size() << "\n";

WeightedTreeDiameter<ll> wd(wg);
cout << wd.len << "\n";
```

## 計算量

- O(n)

## 注意

- 重み付き版は非負の辺重みを前提とします。
- `center()` は直径パスの辺数基準の中央頂点です。
