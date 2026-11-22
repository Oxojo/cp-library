---
title: "Dijkstra"
documentation_of: ./dijkstra.hpp
---

## 概要

非負の辺重みを持つグラフの単一始点最短経路を求めます。

## 使い方

```cpp
Graph<ll> g(n);
g.add(u, v, w);  // 有向辺

auto dist = dijkstra(g, s);

vector<int> parent;
auto dist2 = dijkstra(g, s, &parent);  // 経路復元用
```

## 計算量

- O((n + m) log n)

## 注意

- 負の辺には使えません。
- 到達不能な頂点の距離は `numeric_limits<T>::max() / 4` です。
- 緩和は飽和加算で行い、巨大な重みでもオーバーフローしません。
- `parent` を渡すと、各頂点の直前の頂点が入ります（始点と到達不能頂点は `-1`）。
