---
title: "Manacher"
documentation_of: ./manacher.hpp
---

## 概要

Manacher のアルゴリズムで、各中心に対する最長回文の長さを求めます。
返り値の長さは `2n - 1` で、文字中心と文字間中心が左から交互に並びます。

## 使い方

```cpp
string s = "abacaba";
auto L = manacher(s);
// L[i] = 中心 i の最長回文の長さ
```

## 計算量

- O(n)

## 注意

- 返り値の長さは `2n - 1` です。
- 空文字列に対しては空の配列を返します。
