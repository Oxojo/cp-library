---
title: "Fenwick tree"
documentation_of: ./FenwickTree.hpp
---

## 概要

一点加算・区間和の Fenwick Tree です。

## 使い方

```cpp
FenwickTree<ll> bit(n);
bit.apply(i, x);          // a[i] += x
ll s = bit.prod(l, r);    // sum of [l, r)
ll t = bit.prod(r);       // sum of [0, r)
```

## 計算量

- `apply`: O(log n)
- `prod`: O(log n)

## 注意

- 区間は **半開区間** `[l, r)` です。
- `prod(r)` は `[0, r)` の和です。
