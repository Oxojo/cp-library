---
title: "Graph (adjacency list)"
documentation_of: ./graph.hpp
---

## 概要

辺 `Edge<T>` と隣接リスト `Graph<T>` を提供します。

- `add(from, to, cost)`: 有向辺
- `add_undirected(u, v, cost)`: 無向辺
- `g[v]` で頂点 `v` の辺を走査

## 使い方

```cpp
Graph<ll> g(n);
g.add(u, v, w);           // 有向辺
g.add_undirected(u, v, w); // 無向辺

for (const auto& e : g[v]) {
    int to = e.to;
    ll cost = e.cost;
}
```

## 注意

- `add` は有向辺です。無向辺は `add_undirected` を使ってください。
- `Edge` は `operator int()` を持つため、`int u = e;` と書くと遷移先が得られます。
