---
title: "KMP"
documentation_of: ./kmp.hpp
---

## 概要

`prefix_function(s)` は KMP 法の prefix function（failure function）を返します。
`kmp_search(text, pattern)` は `text` 中の `pattern` の出現開始位置を列挙します。

## 使い方

```cpp
auto pi = prefix_function("ababa");  // {0, 0, 1, 2, 3}

auto pos = kmp_search("abababa", "aba");  // {0, 2, 4}
```

## 計算量

- `prefix_function`: O(n)
- `kmp_search`: O(|text| + |pattern|)

## 注意

- `pattern` が空のとき、`kmp_search` は空の配列を返します。
