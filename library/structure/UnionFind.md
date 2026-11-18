---
title: "Union-Find"
documentation_of: ./UnionFind.hpp
---

## 概要

素集合データ構造です。経路圧縮と union by size を行います。

## 使い方

```cpp
UnionFind uf(n);
uf.unite(u, v);
bool same = uf.same(u, v);
int sz = uf.size(v);
```

## 計算量

- ならし O(α(n))

## 注意

- `const` オブジェクトからも `same` / `size` を呼べます。
- rollback や重み付き Union-Find は提供していません。
