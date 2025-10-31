---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/template/template.hpp
    title: library/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/yosupo/point-add-range-sum.test.cpp
    title: verify/yosupo/point-add-range-sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"library/structure/FenwickTree.hpp\"\n\n#line 2 \"library/template/template.hpp\"\
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
    \ t) {\n\tcout << (t ? \"Yes\" : \"No\") << endl;\n}\n#line 4 \"library/structure/FenwickTree.hpp\"\
    \n\ntemplate <typename T = ll>\nstruct FenwickTree {\n    ll n;\n    vec<T> data;\n\
    \n    FenwickTree() = default;\n    FenwickTree(ll size) { init(size); }\n   \
    \ FenwickTree(vec<T> &a) {\n        init(sz(a));\n        rep(i, sz(a)) add(i,\
    \ a[i]);\n    }\n    \n    void init(ll size) {\n        n = size + 2;\n     \
    \   data.assign(n + 1, {});\n    }\n\n    // sum of [0, k]\n    T sum(ll k) const\
    \ {\n        if (k < 0) return T{};\n        T ret{};\n        for (++k; k > 0;\
    \ k -= k & -k) ret += data[k];\n        return ret;\n    }\n\n    // sum of [l,\
    \ r]\n    inline T sum(ll l, ll r) const { return sum(r) - sum(l - 1); }\n\n \
    \   // value of k\n    inline T operator[](ll k) const { return sum(k) - sum(k\
    \ - 1); }\n\n    // data[k] += x\n    void add(ll k, T x) {\n        for (++k;\
    \ k < n; k += k & -k) data[k] += x;\n    }\n\n    // data[l, ..., r] += x\n  \
    \  void imos(ll l, ll r, T x) {\n        add(l, x);\n        add(r + 1, -x);\n\
    \    }\n    \n    // min i s.t. sum(i) >= w\n    ll lower_bound(T w) {\n     \
    \   if (w <= 0) return 0;\n        ll x = 0;\n        for (ll k = 1 << __lg(n);\
    \ k; k >>= 1) {\n            if (x + k <= n - 1 && data[x + k] < w) {\n      \
    \          w -= data[x + k];\n                x += k;\n            }\n       \
    \ }\n        return x;\n    }\n\n    // min i s.t. sum(i) > w\n    ll upper_bound(T\
    \ w) {\n        if (w < 0) return 0;\n        ll x = 0;\n        for (ll k = 1\
    \ << __lg(n); k; k >>= 1) {\n            if (x + k <= n - 1 && data[x + k] <=\
    \ w) {\n                w -= data[x + k];\n                x += k;\n         \
    \   }\n        }\n        return x;\n    }\n};\n"
  code: "#pragma once\n\n#include \"../template/template.hpp\"\n\ntemplate <typename\
    \ T = ll>\nstruct FenwickTree {\n    ll n;\n    vec<T> data;\n\n    FenwickTree()\
    \ = default;\n    FenwickTree(ll size) { init(size); }\n    FenwickTree(vec<T>\
    \ &a) {\n        init(sz(a));\n        rep(i, sz(a)) add(i, a[i]);\n    }\n  \
    \  \n    void init(ll size) {\n        n = size + 2;\n        data.assign(n +\
    \ 1, {});\n    }\n\n    // sum of [0, k]\n    T sum(ll k) const {\n        if\
    \ (k < 0) return T{};\n        T ret{};\n        for (++k; k > 0; k -= k & -k)\
    \ ret += data[k];\n        return ret;\n    }\n\n    // sum of [l, r]\n    inline\
    \ T sum(ll l, ll r) const { return sum(r) - sum(l - 1); }\n\n    // value of k\n\
    \    inline T operator[](ll k) const { return sum(k) - sum(k - 1); }\n\n    //\
    \ data[k] += x\n    void add(ll k, T x) {\n        for (++k; k < n; k += k & -k)\
    \ data[k] += x;\n    }\n\n    // data[l, ..., r] += x\n    void imos(ll l, ll\
    \ r, T x) {\n        add(l, x);\n        add(r + 1, -x);\n    }\n    \n    //\
    \ min i s.t. sum(i) >= w\n    ll lower_bound(T w) {\n        if (w <= 0) return\
    \ 0;\n        ll x = 0;\n        for (ll k = 1 << __lg(n); k; k >>= 1) {\n   \
    \         if (x + k <= n - 1 && data[x + k] < w) {\n                w -= data[x\
    \ + k];\n                x += k;\n            }\n        }\n        return x;\n\
    \    }\n\n    // min i s.t. sum(i) > w\n    ll upper_bound(T w) {\n        if\
    \ (w < 0) return 0;\n        ll x = 0;\n        for (ll k = 1 << __lg(n); k; k\
    \ >>= 1) {\n            if (x + k <= n - 1 && data[x + k] <= w) {\n          \
    \      w -= data[x + k];\n                x += k;\n            }\n        }\n\
    \        return x;\n    }\n};"
  dependsOn:
  - library/template/template.hpp
  isVerificationFile: false
  path: library/structure/FenwickTree.hpp
  requiredBy: []
  timestamp: '2025-10-31 18:20:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/yosupo/point-add-range-sum.test.cpp
documentation_of: library/structure/FenwickTree.hpp
layout: document
redirect_from:
- /library/library/structure/FenwickTree.hpp
- /library/library/structure/FenwickTree.hpp.html
title: library/structure/FenwickTree.hpp
---
