---
title: "Dinic's maximum flow"
documentation_of: ./dinic.hpp
---

## 概要

Dinic 法による最大流と最小カットを提供します。

## 使い方

```cpp
Dinic<ll> mf(n);
mf.add_edge(u, v, cap);

ll flow = mf.max_flow(s, t);
auto side = mf.min_cut(s);  // s 側の頂点
```

## 計算量

- 一般に O(V^2 E)、実用上は高速

## 注意

- `max_flow` の DFS は再帰実装です（深さはレベルグラフの深さ）。
- `min_cut` は `max_flow` の後に呼んでください。
