---
title: "Graph (adjacency list)"
documentation_of: ./graph.hpp
---

## 概要

辺 `Edge<T>` と隣接リスト `Graph<T>` を提供します。

- `add(from, to, cost, directed = false)`: 既定は**無向辺**
- `read(m, padding = -1, weight = false, directed = false)`: 標準入力から辺を読む
- `g[v]` で頂点 `v` の辺を走査

## 使い方

```cpp
Graph<ll> g(n);
g.add(u, v, w);        // 無向辺
g.add(u, v, w, true);  // 有向辺

for (const auto& e : g[v]) {
    int to = e.to;
    ll cost = e.cost;
}
```

## 注意

- `directed` の既定値が `false`（無向）です。ACL の `add_edge` とは逆なので注意してください。
- `Edge` は `operator int()` を持つため、`int u = e;` と書くと遷移先が得られます。
