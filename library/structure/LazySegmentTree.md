---
title: "Lazy segment tree"
documentation_of: ./LazySegmentTree.hpp
---

## 概要

遅延評価付きセグメント木です。モノイド `(S, op, e)`、作用素モノイド `(F, composition, id)`、
写像 `mapping(f, x)` を指定します。

## 使い方

```cpp
LazySegmentTree seg(v, S{0, 0}, F{1, 0}, op, mapping, comp);

seg.apply(l, r, f);       // [l, r)
S s = seg.prod(l, r);
```

## 計算量

- 構築 O(n)
- `apply` / `prod` / `max_right` / `min_left`: O(log n)

## 注意

- 区間は半開区間 `[l, r)` です。
- `F` は `!=` で比較できる型である必要があります。
