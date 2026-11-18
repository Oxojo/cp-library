---
title: "Lowlink: bridges, articulation points, 2-edge-connected components"
documentation_of: ./lowlink.hpp
---

## 概要

無向グラフの橋・関節点・2辺連結成分を O(n + m) で求めます。
辺 ID で親辺のみをスキップするため、**並列辺や自己ループ**も正しく扱えます。

## 使い方

```cpp
Lowlink low(n);
low.add_edge(u, v);
low.build();

for (int eid : low.bridge_ids) { /* 橋 */ }
for (int v : low.articulation_list) { /* 関節点 */ }
int c = low.two_edge_component[v];
```

## 計算量

- O(n + m)

## 注意

- `build()` は辺を追加した後に 1 回呼んでください。
- `bridge[eid]` / `articulation[v]` でも参照できます。
