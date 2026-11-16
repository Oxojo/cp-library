---
title: "Modular integer"
documentation_of: ./modint.hpp
---

## 概要

`modint<m>` は任意の素数 mod の剰余環を表します。
`mint` は `modint<998244353>` の別名です。

## 使い方

```cpp
mint a = 2, b = 3;
cout << a * b << "\n";        // 6

modint<1000000007> c = 5;
cout << c.inv() << "\n";
```

## 注意

- `inv()` / 除算は mod が素数であることを前提とします。
- 0 の逆元・負の指数は assert で検出します（NDEBUG では無効）。
- 値は `long long` で保持し、`val()` で取得できます。
