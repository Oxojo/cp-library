---
title: "Eertree (palindromic tree)"
documentation_of: ./eertree.hpp
---

## 概要

文字列の回文木（eertree / palindromic tree）を構築します。
頂点 `0` が EVEN、`1` が ODD の根で、新しい回文は出現順に `2, 3, ...` と番号付けされます。

## 使い方

```cpp
Eertree et;
et.build("abacaba");

int n = et.size();                 // 異なる空でない回文の個数
int v = et.prefix_last.back();     // 全体の最長回文接尾辞の頂点
```

`len[v]` は回文の長さ、`parent[v]` は先頭と末尾を削除した回文の頂点、
`link[v]` は最長の proper palindromic suffix の頂点です。

## 計算量

- 構築: O(n × 26)
- 1 文字追加: O(26) 期待（ならし O(1)）

## 注意

- 英小文字のみを扱います。
- `parent` は「先頭と末尾を削除した回文」であり、suffix link とは異なります。
- `build(s)` を呼ぶと内部状態はクリアされます。
