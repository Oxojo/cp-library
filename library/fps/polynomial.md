---
title: "Poly (polynomial)"
documentation_of: ./polynomial.hpp
---

## 概要

`Poly<T, MOD>` は係数を `[0, MOD)` に持つ多項式です。
多項式環の四則演算と、微分・積分・Taylor shift などを提供します。

`FPS<T, MOD>` はこの型を継承し、形式的べき級数の演算を追加します。

## 使い方

```cpp
Poly<ll> f{1, 2, 3}, g{1, 1};

auto h = f * g;              // 畳み込み
auto qr = f.div_mod(g);      // {商, 剰余}
auto d = f.diff();           // 微分
auto i = f.integral();       // 積分
auto s = f.shift(5);         // f(x + 5)
```

## 計算量

- 加算・減算・スカラー倍: O(n)
- 乗算: O(n log n)
- 除算・剰余: O(n log n)
- 微分・積分: O(n)
- Taylor shift: O(n log n)

## 注意

- `MOD` はコンパイル時の NTT-friendly な素数です。`Poly<ll, 1004535809>` のように切り替えます。
- 除算・積分は `MOD` が素数であることを前提とします。
- 除算は `div_mod` を使います。除数が零多項式の場合は assert で検出します。
- 係数は各演算で `[0, MOD)` に還元されます。
- `T` は整数型を想定しています。
