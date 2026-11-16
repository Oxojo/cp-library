---
title: "Segment tree"
documentation_of: ./SegmentTree.hpp
---

## 概要

モノイド `(S, op, e)` のセグメント木です。

## 使い方

```cpp
auto op = [](ll a, ll b) { return a + b; };
SegmentTree seg(n, 0LL, op);        // CTAD

seg.set(i, x);
ll s = seg.prod(l, r);              // [l, r)
int r2 = seg.max_right(l, [](ll s) { return s <= limit; });
```

## 計算量

- 構築 O(n)
- `set` / `prod` / `max_right` / `min_left`: O(log n)

## 注意

- 区間は半開区間 `[l, r)` です。
- `op` を値で保持します。CTAD でラムダを渡すと `std::function` を経由しません。
