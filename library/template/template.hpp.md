---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/fps/fps.hpp
    title: library/fps/fps.hpp
  - icon: ':warning:'
    path: library/math/modint.hpp
    title: library/math/modint.hpp
  - icon: ':heavy_check_mark:'
    path: library/math/modula.hpp
    title: library/math/modula.hpp
  - icon: ':heavy_check_mark:'
    path: library/structure/FenwickTree.hpp
    title: library/structure/FenwickTree.hpp
  - icon: ':heavy_check_mark:'
    path: library/structure/UnionFind.hpp
    title: library/structure/UnionFind.hpp
  - icon: ':warning:'
    path: library/tree/CentroidDecomposition.hpp
    title: library/tree/CentroidDecomposition.hpp
  - icon: ':warning:'
    path: library/tree/FrequencyTreeDistance.hpp
    title: library/tree/FrequencyTreeDistance.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/yosupo/convolution-mod.test.cpp
    title: verify/yosupo/convolution-mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/yosupo/point-add-range-sum.test.cpp
    title: verify/yosupo/point-add-range-sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/yosupo/unionfind.test.cpp
    title: verify/yosupo/unionfind.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"library/template/template.hpp\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n#define MM << ' ' <<\nusing ll = long long;\nusing ld =\
    \ long double;\nusing pll = pair<ll, ll>;\nusing vl = vector<ll>;\ntemplate <class\
    \ T> using vec = vector<T>;\ntemplate <class T> using vv = vec<vec<T>>;\ntemplate\
    \ <class T> using vvv = vv<vec<T>>;\ntemplate <class T> using minpq = priority_queue<T,\
    \ vector<T>, greater<T>>;\n#define rep(i, r) for(ll i = 0; i < (r); i++)\n#define\
    \ reps(i, l, r) for(ll i = (l); i < (r); i++)\n#define rrep(i, l, r) for(ll i\
    \ = (r) - 1; i >= l; i--)\ntemplate <class T> void uniq(T &a) { sort(all(a));\
    \ erase(unique(all(a)), a.end()); }\n#define all(a) (a).begin(), (a).end()\n#define\
    \ sz(a) (ll)(a).size()\nconst ll INF = numeric_limits<ll>::max() / 4;\nconst ld\
    \ inf = numeric_limits<ld>::max() / 2;\nconst ll mod1 = 1000000007;\nconst ll\
    \ mod2 = 998244353;\nconst ld pi = 3.141592653589793238;\ntemplate <class T> void\
    \ rev(T &a) { reverse(all(a)); }\nll popcnt(ll a) { return __builtin_popcountll(a);\
    \ }\ntemplate<typename T>\nbool chmax(T &a, const T& b) { return a < b ? a = b,\
    \ true : false; }\ntemplate<typename T>\nbool chmin(T &a, const T& b) { return\
    \ a > b ? a = b, true : false; }\ntemplate <typename T1, typename T2>\nostream&\
    \ operator<<(ostream& os, const pair<T1, T2>& p) {\n\tos << p.first << \" \" <<\
    \ p.second;\n\treturn os;\n}\ntemplate <typename T1, typename T2>\nistream& operator>>(istream&\
    \ is, pair<T1, T2>& p) {\n\tis >> p.first >> p.second;\n\treturn is;\n}\ntemplate\
    \ <typename T>\nostream& operator<<(ostream& os, const vec<T>& v) {\n\trep(i,\
    \ sz(v)) {\n\t\tos << v[i] << \" \\n\"[i + 1 == sz(v)];\n\t}\n\treturn os;\n}\n\
    template <typename T>\nistream& operator>>(istream& is, vec<T>& v) {\n\tfor (T&\
    \ in : v) is >> in;\n\treturn is;\n}\nvoid yesno(bool t) {\n\tcout << (t ? \"\
    Yes\" : \"No\") << endl;\n}\n"
  code: "#pragma once\n\n#include <bits/stdc++.h>\nusing namespace std;\n#define MM\
    \ << ' ' <<\nusing ll = long long;\nusing ld = long double;\nusing pll = pair<ll,\
    \ ll>;\nusing vl = vector<ll>;\ntemplate <class T> using vec = vector<T>;\ntemplate\
    \ <class T> using vv = vec<vec<T>>;\ntemplate <class T> using vvv = vv<vec<T>>;\n\
    template <class T> using minpq = priority_queue<T, vector<T>, greater<T>>;\n#define\
    \ rep(i, r) for(ll i = 0; i < (r); i++)\n#define reps(i, l, r) for(ll i = (l);\
    \ i < (r); i++)\n#define rrep(i, l, r) for(ll i = (r) - 1; i >= l; i--)\ntemplate\
    \ <class T> void uniq(T &a) { sort(all(a)); erase(unique(all(a)), a.end()); }\n\
    #define all(a) (a).begin(), (a).end()\n#define sz(a) (ll)(a).size()\nconst ll\
    \ INF = numeric_limits<ll>::max() / 4;\nconst ld inf = numeric_limits<ld>::max()\
    \ / 2;\nconst ll mod1 = 1000000007;\nconst ll mod2 = 998244353;\nconst ld pi =\
    \ 3.141592653589793238;\ntemplate <class T> void rev(T &a) { reverse(all(a));\
    \ }\nll popcnt(ll a) { return __builtin_popcountll(a); }\ntemplate<typename T>\n\
    bool chmax(T &a, const T& b) { return a < b ? a = b, true : false; }\ntemplate<typename\
    \ T>\nbool chmin(T &a, const T& b) { return a > b ? a = b, true : false; }\ntemplate\
    \ <typename T1, typename T2>\nostream& operator<<(ostream& os, const pair<T1,\
    \ T2>& p) {\n\tos << p.first << \" \" << p.second;\n\treturn os;\n}\ntemplate\
    \ <typename T1, typename T2>\nistream& operator>>(istream& is, pair<T1, T2>& p)\
    \ {\n\tis >> p.first >> p.second;\n\treturn is;\n}\ntemplate <typename T>\nostream&\
    \ operator<<(ostream& os, const vec<T>& v) {\n\trep(i, sz(v)) {\n\t\tos << v[i]\
    \ << \" \\n\"[i + 1 == sz(v)];\n\t}\n\treturn os;\n}\ntemplate <typename T>\n\
    istream& operator>>(istream& is, vec<T>& v) {\n\tfor (T& in : v) is >> in;\n\t\
    return is;\n}\nvoid yesno(bool t) {\n\tcout << (t ? \"Yes\" : \"No\") << endl;\n\
    }"
  dependsOn: []
  isVerificationFile: false
  path: library/template/template.hpp
  requiredBy:
  - library/structure/FenwickTree.hpp
  - library/structure/UnionFind.hpp
  - library/math/modula.hpp
  - library/math/modint.hpp
  - library/fps/fps.hpp
  - library/tree/CentroidDecomposition.hpp
  - library/tree/FrequencyTreeDistance.hpp
  timestamp: '2025-10-31 18:20:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/yosupo/unionfind.test.cpp
  - verify/yosupo/point-add-range-sum.test.cpp
  - verify/yosupo/convolution-mod.test.cpp
documentation_of: library/template/template.hpp
layout: document
redirect_from:
- /library/library/template/template.hpp
- /library/library/template/template.hpp.html
title: library/template/template.hpp
---
