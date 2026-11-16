---
title: "2D point"
documentation_of: ./point.hpp
---

## 概要

`long double` の 2 次元点 `Point` と、`eps` を用いた比較・符号関数を提供します。

- `dot` / `cross` / `norm`（二乗ノルム）/ `abs` / `arg`
- `rotate(radian)`、四則演算、比較、入出力

## 使い方

```cpp
Point a(1, 2), b(3, 4);
ld d = (b - a).abs();
ld c = a.cross(b);
```

## 注意

- 浮動小数（`long double`）実装です。座標が大きい場合や厳密判定が必要な場合は整数幾何を使ってください。
- `eps = 1e-10` の絶対比較です。
- `operator<` は eps 比較のため、厳密には strict weak ordering ではありません。ソート用途では注意してください。
