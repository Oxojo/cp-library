---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/template/template.hpp
    title: library/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"library/tree/CentroidDecomposition.hpp\"\n\n#line 2 \"library/template/template.hpp\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\n#define MM << ' ' <<\nusing\
    \ ll = long long;\nusing ld = long double;\nusing pll = pair<ll, ll>;\nusing vl\
    \ = vector<ll>;\ntemplate <class T> using vec = vector<T>;\ntemplate <class T>\
    \ using vv = vec<vec<T>>;\ntemplate <class T> using vvv = vv<vec<T>>;\ntemplate\
    \ <class T> using minpq = priority_queue<T, vector<T>, greater<T>>;\n#define rep(i,\
    \ r) for(ll i = 0; i < (r); i++)\n#define reps(i, l, r) for(ll i = (l); i < (r);\
    \ i++)\n#define rrep(i, l, r) for(ll i = (r) - 1; i >= l; i--)\ntemplate <class\
    \ T> void uniq(T &a) { sort(all(a)); erase(unique(all(a)), a.end()); }\n#define\
    \ all(a) (a).begin(), (a).end()\n#define sz(a) (ll)(a).size()\nconst ll INF =\
    \ numeric_limits<ll>::max() / 4;\nconst ld inf = numeric_limits<ld>::max() / 2;\n\
    const ll mod1 = 1000000007;\nconst ll mod2 = 998244353;\nconst ld pi = 3.141592653589793238;\n\
    template <class T> void rev(T &a) { reverse(all(a)); }\nll popcnt(ll a) { return\
    \ __builtin_popcountll(a); }\ntemplate<typename T>\nbool chmax(T &a, const T&\
    \ b) { return a < b ? a = b, true : false; }\ntemplate<typename T>\nbool chmin(T\
    \ &a, const T& b) { return a > b ? a = b, true : false; }\ntemplate <typename\
    \ T1, typename T2>\nostream& operator<<(ostream& os, const pair<T1, T2>& p) {\n\
    \tos << p.first << \" \" << p.second;\n\treturn os;\n}\ntemplate <typename T1,\
    \ typename T2>\nistream& operator>>(istream& is, pair<T1, T2>& p) {\n\tis >> p.first\
    \ >> p.second;\n\treturn is;\n}\ntemplate <typename T>\nostream& operator<<(ostream&\
    \ os, const vec<T>& v) {\n\trep(i, sz(v)) {\n\t\tos << v[i] << \" \\n\"[i + 1\
    \ == sz(v)];\n\t}\n\treturn os;\n}\ntemplate <typename T>\nistream& operator>>(istream&\
    \ is, vec<T>& v) {\n\tfor (T& in : v) is >> in;\n\treturn is;\n}\nvoid yesno(bool\
    \ t) {\n\tcout << (t ? \"Yes\" : \"No\") << endl;\n}\n#line 4 \"library/tree/CentroidDecomposition.hpp\"\
    \ntemplate <class G>\nstruct CentroidDecomposition {\n\tconst G &g;\n\tvl sub;\n\
    \tvec<bool> v;\n\tvv<ll> tree;\n\tll root;\n\n\tCentroidDecomposition(const G\
    \ &g_, bool isbuild = true) : g(g_) {\n\t\tsub.resize(sz(g), 0ll);\n\t\tv.resize(sz(g),\
    \ false);\n\t\tif (isbuild) build();\n\t}\n\tvoid build() {\n\t\ttree.resize(sz(g));\n\
    \t\troot = build_dfs(0);\n\t}\n\tll get_size(ll cur, ll par) {\n\t\tsub[cur] =\
    \ 1;\n\t\tfor (auto &dst : g[cur]) {\n\t\t\tif (dst == par || v[dst]) continue;\n\
    \t\t\tsub[cur] += get_size(dst, cur);\n\t\t}\n\t\treturn sub[cur];\n\t}\n\tll\
    \ get_centroid(ll cur, ll par, ll mid) {\n\t\tfor (auto &dst : g[cur]) {\n\t\t\
    \tif (dst == par || v[dst]) continue;\n\t\t\tif (sub[dst] > mid) return get_centroid(dst,\
    \ cur, mid);\n\t\t}\n\t\treturn cur;\n\t}\n\tll build_dfs(ll cur) {\n\t\tll centroid\
    \ = get_centroid(cur, -1, get_size(cur, -1) / 2);\n\t\tv[centroid] = true;\n\t\
    \tfor (auto &dst : g[centroid]) {\n\t\t\tif (!v[dst]) {\n\t\t\t\tll nxt = build_dfs(dst);\n\
    \t\t\t\tif (centroid != nxt) tree[centroid].emplace_back(nxt);\n\t\t\t}\n\t\t\
    }\n\t\tv[centroid] = false;\n\t\treturn centroid;\n\t}\n};\n"
  code: "#pragma once\n\n#include \"../template/template.hpp\"\ntemplate <class G>\n\
    struct CentroidDecomposition {\n\tconst G &g;\n\tvl sub;\n\tvec<bool> v;\n\tvv<ll>\
    \ tree;\n\tll root;\n\n\tCentroidDecomposition(const G &g_, bool isbuild = true)\
    \ : g(g_) {\n\t\tsub.resize(sz(g), 0ll);\n\t\tv.resize(sz(g), false);\n\t\tif\
    \ (isbuild) build();\n\t}\n\tvoid build() {\n\t\ttree.resize(sz(g));\n\t\troot\
    \ = build_dfs(0);\n\t}\n\tll get_size(ll cur, ll par) {\n\t\tsub[cur] = 1;\n\t\
    \tfor (auto &dst : g[cur]) {\n\t\t\tif (dst == par || v[dst]) continue;\n\t\t\t\
    sub[cur] += get_size(dst, cur);\n\t\t}\n\t\treturn sub[cur];\n\t}\n\tll get_centroid(ll\
    \ cur, ll par, ll mid) {\n\t\tfor (auto &dst : g[cur]) {\n\t\t\tif (dst == par\
    \ || v[dst]) continue;\n\t\t\tif (sub[dst] > mid) return get_centroid(dst, cur,\
    \ mid);\n\t\t}\n\t\treturn cur;\n\t}\n\tll build_dfs(ll cur) {\n\t\tll centroid\
    \ = get_centroid(cur, -1, get_size(cur, -1) / 2);\n\t\tv[centroid] = true;\n\t\
    \tfor (auto &dst : g[centroid]) {\n\t\t\tif (!v[dst]) {\n\t\t\t\tll nxt = build_dfs(dst);\n\
    \t\t\t\tif (centroid != nxt) tree[centroid].emplace_back(nxt);\n\t\t\t}\n\t\t\
    }\n\t\tv[centroid] = false;\n\t\treturn centroid;\n\t}\n};"
  dependsOn:
  - library/template/template.hpp
  isVerificationFile: false
  path: library/tree/CentroidDecomposition.hpp
  requiredBy: []
  timestamp: '2025-10-31 18:20:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/tree/CentroidDecomposition.hpp
layout: document
redirect_from:
- /library/library/tree/CentroidDecomposition.hpp
- /library/library/tree/CentroidDecomposition.hpp.html
title: library/tree/CentroidDecomposition.hpp
---
