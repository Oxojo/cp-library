---
title: "Suffix array / LCP array"
documentation_of: ./suffix_array.hpp
---

## 概要

`suffix_array(s)` は文字列または整数列 `s` の suffix array を返します。
`lcp_array(s, sa)` は隣接する suffix の最長共通接頭辞長を返します。

## 使い方

```cpp
string s = "banana";
auto sa = suffix_array(s);       // {5, 3, 1, 0, 4, 2}
auto lcp = lcp_array(s, sa);     // {1, 3, 0, 0, 2}

vector<ll> a = {3, -1, 4, -1, 5};
auto sa2 = suffix_array(a);
auto lcp2 = lcp_array(a, sa2);
```

## 計算量

- suffix array: O(n log n)
- LCP array: O(n)

## 注意

- 文字列は各文字を整数として比較します。整数列は値の大小で比較します。
- suffix array の構築前に座標圧縮を行うため、値の種類が多くても O(n log n) です。
- `lcp[i]` は `sa[i]` と `sa[i+1]` の LCP です。
- 空列の suffix array は空、LCP array も空です。
