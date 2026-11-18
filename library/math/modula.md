---
title: "Modular arithmetic utilities"
documentation_of: ./modula.hpp
---

## 概要

`long long` 用の mod 演算をまとめたヘッダです。

- `modmul`: `__int128` を使った積
- `modpow`: 累乗
- `modinv`: 拡張ユークリッドによる逆元
- `modlog`: 離散対数（拡張 BSGS、合成数 mod 対応）
- `modsqrt`: 平方根（奇素数 mod）

## 使い方

```cpp
ll x = modpow<ll>(2, 10, 1000000007);   // 1024
ll y = modinv(3, 7);                    // 5
ll z = modlog<ll>(2, 4, 7);             // 2（なければ -1）
ll w = modsqrt(4, 7);                   // 2 or 5（なければ -1）
```

## 計算量

- `modpow`: O(log n)
- `modlog`: O(sqrt(p)) 程度
- `modsqrt`: O(log^2 p)

## 注意

- `modinv` は gcd が 1 であることが必要です。
- `modlog` は `unordered_map` を使うため、Codeforces などではハック耐性が低いです。
- `modsqrt` は奇素数 mod を前提とします（`p = 2` は別扱い）。
