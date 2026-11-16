---
title: "Inversion number"
documentation_of: ./inversion-number.hpp
---

## 概要

配列の転倒数（`i < j` かつ `a[i] > a[j]` となる組の数）を O(n log n) で求めます。
座標圧縮した値を Fenwick Tree に載せて数えます。

## 使い方

```cpp
vl a{3, 1, 2};
long long inv = inversion_num(a);  // 2
```

## 計算量

- O(n log n)、追加メモリ O(n)

## 注意

- 等しい要素は転倒として数えません（狭義）。
- 返り値は `long long` です。
