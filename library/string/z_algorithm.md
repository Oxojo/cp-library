---
title: "Z algorithm"
documentation_of: ./z_algorithm.hpp
---

## 概要

`z[i]` を「`s` と `s[i..]` の最長共通接頭辞長」とする配列を返します。
`z[0]` は `s.size()` です。

## 使い方

```cpp
string s = "abacaba";
auto z = z_algorithm(s);  // {7, 0, 1, 0, 3, 0, 1}
```

`string` だけでなく `vector<int>` などにも使えます。

## 計算量

- O(n)

## 注意

- `z[0] == n` です。
