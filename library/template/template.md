---
title: "Template utilities"
documentation_of: ./template.hpp
---

## 概要

競プロ用の型エイリアス・マクロ・入出力ユーティリティをまとめたヘッダです。

- `ll` / `ld` / `i128` などの型
- `rep` / `reps` / `rrep` などのループマクロ
- `in(...)` / `out(...)` の可変長入出力
- `chmax` / `chmin`、`mkuniq`、`mkcum`、`i128` の入出力など

## 使い方

```cpp
#include "library/template/template.hpp"

int main() {
    ll n;
    in(n);
    vl a(n);
    in(a);
    out(Sum(a), "\n");
}
```

## 注意

- `library/` の各ヘッダは `template.hpp` に依存せず単体で使えます。
- `rep(i, n)` は条件判定のたびに `n` を評価します。
