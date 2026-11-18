---
title: "Dijkstra with path restoration"
documentation_of: ./dijkstra_restore.hpp
---

## 概要

Dijkstra で距離と「直前の頂点」を求めます。最短経路の復元に使えます。

## 使い方

```cpp
auto res = dijkstra_restore(g, s);
if (res[t].first != INF) {
    for (int v = t; v != -1; v = res[v].second) {
        // t -> s の順に並ぶ
    }
}
```

## 計算量

- O((n + m) log n)

## 注意

- `res[v] = {距離, 直前の頂点}`、始点の直前は `-1` です。
- 到達不能は `{INF, -1}` です。
