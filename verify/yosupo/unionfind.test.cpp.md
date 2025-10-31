---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/structure/UnionFind.hpp
    title: library/structure/UnionFind.hpp
  - icon: ':question:'
    path: library/template/template.hpp
    title: library/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "#line 1 \"verify/yosupo/unionfind.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\
    \n\n#line 2 \"library/template/template.hpp\"\n\n#include <bits/stdc++.h>\nusing\
    \ namespace std;\n#define MM << ' ' <<\nusing ll = long long;\nusing ld = long\
    \ double;\nusing pll = pair<ll, ll>;\nusing vl = vector<ll>;\ntemplate <class\
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
    Yes\" : \"No\") << endl;\n}\n#line 2 \"library/structure/UnionFind.hpp\"\n\n#line\
    \ 4 \"library/structure/UnionFind.hpp\"\nstruct UnionFind {\n\tvl data;\n\n\t\
    UnionFind(ll n) : data(n, -1) {}\n\n\tll find(ll k) {\n\t\treturn data[k] < 0\
    \ ? k : data[k] = find(data[k]);\n\t}\n\n\tll unite(ll x, ll y) {\n\t\tx = find(x),\
    \ y = find(y);\n\t\tif (x == y) return false;\n\t\tif (data[x] > data[y]) swap(x,\
    \ y);\n\t\tdata[x] += data[y];\n\t\tdata[y] = x;\n\t\treturn true;\n\t}\n\n\t\
    ll size(ll k) {\n\t\treturn -data[find(k)];\n\t}\n\n\tbool same(ll x, ll y) {\n\
    \t\treturn find(x) == find(y);\n\t}\n};\n#line 5 \"verify/yosupo/unionfind.test.cpp\"\
    \n\nvoid solve() {\n    ll n, q; cin >> n >> q;\n\tUnionFind uf(n);\n\twhile (q--)\
    \ {\n\t\tll t; cin >> t;\n\t\tif (t == 0) {\n\t\t\tll u, v; cin >> u >> v;\n\t\
    \t\tuf.unite(u, v);\n\t\t}\n\t\telse {\n\t\t\tll u, v; cin >> u >> v;\n\t\t\t\
    cout << uf.same(u, v) << endl;\n\t\t}\n\t}\n}\nint main() {\n    ll T = 1;\n \
    \   // cin >> T;\n    while (T--) solve();\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include\
    \ \"../../library/template/template.hpp\"\n#include \"../../library/structure/UnionFind.hpp\"\
    \n\nvoid solve() {\n    ll n, q; cin >> n >> q;\n\tUnionFind uf(n);\n\twhile (q--)\
    \ {\n\t\tll t; cin >> t;\n\t\tif (t == 0) {\n\t\t\tll u, v; cin >> u >> v;\n\t\
    \t\tuf.unite(u, v);\n\t\t}\n\t\telse {\n\t\t\tll u, v; cin >> u >> v;\n\t\t\t\
    cout << uf.same(u, v) << endl;\n\t\t}\n\t}\n}\nint main() {\n    ll T = 1;\n \
    \   // cin >> T;\n    while (T--) solve();\n}"
  dependsOn:
  - library/template/template.hpp
  - library/structure/UnionFind.hpp
  isVerificationFile: true
  path: verify/yosupo/unionfind.test.cpp
  requiredBy: []
  timestamp: '2025-11-01 06:58:30+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/yosupo/unionfind.test.cpp
layout: document
redirect_from:
- /verify/verify/yosupo/unionfind.test.cpp
- /verify/verify/yosupo/unionfind.test.cpp.html
title: verify/yosupo/unionfind.test.cpp
---
