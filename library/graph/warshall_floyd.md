---
title: "Warshall-Floyd (all pairs shortest paths)"
documentation_of: ./warshall_floyd.hpp
---

## 概要

全点対最短経路を O(n^3) で求めます。距離行列を直接更新します。

## 使い方

```cpp
vector<vector<ll>> d(n, vector<ll>(n, INF));
for (int i = 0; i < n; i++) d[i][i] = 0;
d[u][v] = min(d[u][v], w);

bool ok = warshall_floyd(d);  // false なら負閉路
```

## 計算量

- O(n^3)

## 注意

- 到達不能は `INF`（既定 `max/4`）で初期化してください。
- 負閉路がある場合は `false` を返します。
