---
title: "Aho-Corasick"
documentation_of: ./aho_corasick.hpp
---

## 概要

複数のパターンから trie と failure link を構築し、テキスト中の出現回数をまとめて数えます。

## 使い方

```cpp
AhoCorasick ac;
ac.add("he");
ac.add("she");
ac.build();

auto cnt = ac.match_count("ushers");  // 各パターンの出現回数
```

`build()` 後の `nodes[v].parent` / `nodes[v].link` で trie の親と suffix link を参照できます。
`nodes[0]` は root です。

## 計算量

- 構築: O(総パターン長 × 26)
- 検索: O(|text| + 総パターン長)

## 注意

- 英小文字のみを扱います。
- `add()` をすべて呼んだ後に `build()` を呼んでください。
- `match_count()` は `build()` 後に呼んでください。
