---
title: "NTT / convolution"
documentation_of: ./ntt.hpp
---

## 概要

`NTT<MOD>` は NTT-friendly な素数 `MOD` に対する数論変換と畳み込みを提供します。
原始根は初回利用時に自動検出し、変換用のテーブルも static に一度だけ構築します。

## 使い方

```cpp
vector<ll> a{1, 2, 3}, b{4, 5};

// 長さ a.size() + b.size() - 1
auto c = NTT<998244353>::convolution(a, b);
```

`Poly` / `FPS` の乗算は内部でこの畳み込みを使います。

## 計算量

- 畳み込み: O(n log n)
- ただし `min(a.size(), b.size()) <= 60` のときは naive な O(nm)

## 注意

- `MOD` は NTT-friendly な素数である必要があります。`(MOD - 1) % 2^k == 0` を満たさない長さは assert で検出します。
- 係数は `[0, MOD)` に還元されていることを前提とします。
- 変換テーブルは `MOD` ごとに static に保持されます。
