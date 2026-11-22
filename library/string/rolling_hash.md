---
title: "Rolling hash"
documentation_of: ./rolling_hash.hpp
---

## 概要

mod `2^61 - 1` のローリングハッシュです。
部分文字列のハッシュ取得と、2 つの suffix の LCP 計算を提供します。

## 使い方

```cpp
RollingHash rh;
rh.build("abacaba");

auto h1 = rh.get(0, 3);   // "aba"
auto h2 = rh.get(4, 7);   // "aba"
// h1 == h2

int l = rh.lcp(0, 4, 3);  // 3
```

## 計算量

- 構築: O(n)
- `get`: O(1)
- `lcp`: O(log n)

## 注意

- ハッシュの衝突は原理的に避けられません。厳密性が必要な場合は suffix array などを使ってください。
- `get(l, r)` は半開区間 `[l, r)` です。
- `lcp(a, b, lim)` は `a, b` から始まる suffix の LCP を `lim` までで打ち切って返します。
