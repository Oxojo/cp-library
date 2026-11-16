---
title: "Tree centroids"
documentation_of: ./tree_centroid.hpp
---

## 概要

木の重心をすべて求めます。重心は高々 2 個です。

## 使い方

```cpp
TreeCentroid tc(g);
for (int v : tc.centroids) { /* ... */ }
```

## 計算量

- O(n)

## 注意

- 頂点 `v` を除いた各連結成分のサイズが `n/2` 以下になる `v` を返します。
