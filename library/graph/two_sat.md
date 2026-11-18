---
title: "2-SAT"
documentation_of: ./two_sat.hpp
---

## 概要

2-SAT を SCC で解きます。変数は 0-indexed です。

## 使い方

```cpp
TwoSAT sat(n);
sat.add_clause(i, true, j, false);  // (x_i = true) OR (x_j = false)

if (sat.satisfiable()) {
    bool xi = sat.answer[i];
}
```

## 計算量

- 節の追加 O(1)、判定 O(n + m)

## 注意

- `satisfiable()` を呼ぶまで `answer` は有効ではありません。
