---
title: "Sort points by argument"
documentation_of: ./argsort.hpp
---

## 概要

点列を原点まわりの偏角でソートします（範囲は `[-π, π)`）。

## 使い方

```cpp
vector<Point> ps{{1, 0}, {0, 1}, {-1, 0}};
argsort(ps);
```

## 計算量

- O(n log n)

## 注意

- eps を用いた比較のため、原点付近や同一直線上の点では順序が不安定になることがあります。
