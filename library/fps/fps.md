---
title: "Formal power series"
documentation_of: ./fps.hpp
---

## 概要

`FPS<T, MOD>` は `Poly<T, MOD>` を継承した形式的べき級数です。
`inv` / `log` / `exp` / `sqrt` / `pow` と、多項式の四則演算を提供します。
`shift` / `diff` / `integral` / `div_mod` などは `Poly` から継承されます。
NTT と多項式環の実装は `ntt.hpp` / `polynomial.hpp` に分離されています。

## 使い方

```cpp
FPS<ll> f{1, 2, 3};
auto g = f.inv(10);     // 1/f mod x^10
auto h = f.log(10);     // f[0] == 1
auto e = h.exp(10);     // exp(log f)
auto p = f.pow(5, 10);  // f^5 mod x^10
```

別の NTT-friendly 素数を使う場合は、`MOD` をテンプレート引数で指定します。

```cpp
FPS<ll, 1004535809> f{1, 2, 3};
```

## 計算量

- 乗算: O(n log n)
- `inv`: O(n log n)
- `log`: O(n log n)
- `exp`: O(n log n)
- `sqrt`: O(n log n)
- `pow`: O(n log n)

## 注意

- `MOD` はコンパイル時の NTT-friendly 素数です。実行時に切り替える `set_mod` はありません。
- `log` は `f[0] == 1`、`exp` は `f[0] == 0`、`inv` は `f[0] != 0` を要求します。
- `sqrt` は平方根が存在しない場合に空の列を返します。
- 結果は指定した長さ `n` に 0 埋めされます。
- `NDEBUG` では assert が無効になるため、前提条件は呼び出し側で保証してください。
