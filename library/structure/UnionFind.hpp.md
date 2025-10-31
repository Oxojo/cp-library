---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/template/template.hpp
    title: library/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/yosupo/unionfind.test.cpp
    title: verify/yosupo/unionfind.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"library/structure/UnionFind.hpp\"\n\n#line 2 \"library/template/template.hpp\"\
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
    \ t) {\n\tcout << (t ? \"Yes\" : \"No\") << endl;\n}\n#line 4 \"library/structure/UnionFind.hpp\"\
    \nstruct UnionFind {\n\tvl data;\n\n\tUnionFind(ll n) : data(n, -1) {}\n\n\tll\
    \ find(ll k) {\n\t\treturn data[k] < 0 ? k : data[k] = find(data[k]);\n\t}\n\n\
    \tll unite(ll x, ll y) {\n\t\tx = find(x), y = find(y);\n\t\tif (x == y) return\
    \ false;\n\t\tif (data[x] > data[y]) swap(x, y);\n\t\tdata[x] += data[y];\n\t\t\
    data[y] = x;\n\t\treturn true;\n\t}\n\n\tll size(ll k) {\n\t\treturn -data[find(k)];\n\
    \t}\n\n\tbool same(ll x, ll y) {\n\t\treturn find(x) == find(y);\n\t}\n};\n"
  code: "#pragma once\n\n#include \"../template/template.hpp\"\nstruct UnionFind {\n\
    \tvl data;\n\n\tUnionFind(ll n) : data(n, -1) {}\n\n\tll find(ll k) {\n\t\treturn\
    \ data[k] < 0 ? k : data[k] = find(data[k]);\n\t}\n\n\tll unite(ll x, ll y) {\n\
    \t\tx = find(x), y = find(y);\n\t\tif (x == y) return false;\n\t\tif (data[x]\
    \ > data[y]) swap(x, y);\n\t\tdata[x] += data[y];\n\t\tdata[y] = x;\n\t\treturn\
    \ true;\n\t}\n\n\tll size(ll k) {\n\t\treturn -data[find(k)];\n\t}\n\n\tbool same(ll\
    \ x, ll y) {\n\t\treturn find(x) == find(y);\n\t}\n};"
  dependsOn:
  - library/template/template.hpp
  isVerificationFile: false
  path: library/structure/UnionFind.hpp
  requiredBy: []
  timestamp: '2025-11-01 02:09:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/yosupo/unionfind.test.cpp
documentation_of: library/structure/UnionFind.hpp
layout: document
redirect_from:
- /library/library/structure/UnionFind.hpp
- /library/library/structure/UnionFind.hpp.html
title: library/structure/UnionFind.hpp
---
