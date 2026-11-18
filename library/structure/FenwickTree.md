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
ll s = bit.prod(l, r);    // sum of [l, r]（閉区間）
```

## 計算量

- `apply`: O(log n)
- `prod`: O(log n)

## 注意

- 区間は**閉区間** `[l, r]` です。半開区間ではありません。
- `prod` は範囲外の添字をクランプします。
