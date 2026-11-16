---
title: "Bellman-Ford"
documentation_of: ./bellman_ford.hpp
---

## 概要

負の辺を含むグラフの単一始点最短経路を求め、始点から到達可能な負閉路を検出します。

## 使い方

```cpp
Edges<ll> es;
es.emplace_back(u, v, w);
auto res = bellman_ford<ll>(n, es, s);
if (res.negative_cycle) {
    // 負閉路あり
}
```

## 計算量

- O(n m)

## 注意

- 到達不能な頂点の距離は `numeric_limits<T>::max() / 4` です。
- 始点から到達不能な負閉路は検出しません。
