---
title: "Formal power series"
documentation_of: ./fps.hpp
---

## 概要

形式的冪級数 `FPS<T>`（`std::vector<T>` の派生）です。NTT による畳み込みと、
`inv` / `log` / `exp` / `sqrt` / `pow` / `shift` / `diff` / `integral` / `div_mod` などを提供します。
係数は既定で mod 998244353 として扱います。

## 使い方

```cpp
FPS<ll> f{1, 2, 3};
auto g = f.inv(10);     // 1/f mod x^10
auto h = f.log(10);     // f[0] == 1
auto e = h.exp(10);     // exp(log f)
auto p = f.pow(5, 10);  // f^5 mod x^10
```

## 計算量

- 乗算: O(n log n)
- `inv`: O(n log n)
- `log` / `exp` / `sqrt` / `pow`: O(n log^2 n)（現行実装）

## 注意

- 係数は各演算で mod に還元されます。
- 畳み込みは長さ `2^23` 以下（assert）。`set_mod` は NTT-friendly な素数と原始根が必要です。
- `log` は `f[0] == 1`、`exp` は `f[0] == 0` を要求します。
- `NDEBUG` では assert が無効になるため、前提条件は呼び出し側で保証してください。
