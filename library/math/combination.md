---
title: "Binomial coefficients"
documentation_of: ./combination.hpp
---

## 概要

素数 mod の階乗・逆階乗を前計算し、`C` / `P` / `H` を提供します。
mod は実行時に指定できます。

## 使い方

```cpp
Combination comb(200000);            // mod 998244353
Combination comb2(200000, 1000000007);

ll x = comb.C(n, k);
ll y = comb.P(n, k);
ll z = comb.H(n, k);                 // nHk
```

## 計算量

- 前計算 O(n)
- クエリ O(1)

## 注意

- `0 <= n <= コンストラクタに渡した n` かつ `n < mod` を満たす必要があります。
- mod が素数でない場合は正しく動きません。
