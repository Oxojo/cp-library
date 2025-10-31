---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/template/template.hpp
    title: library/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/fps/fps.hpp
    title: library/fps/fps.hpp
  - icon: ':heavy_check_mark:'
    path: library/tree/FrequencyTreeDistance.hpp
    title: library/tree/FrequencyTreeDistance.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/yosupo/convolution-mod.test.cpp
    title: verify/yosupo/convolution-mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/yosupo/frequency-tree-distance.test.cpp
    title: verify/yosupo/frequency-tree-distance.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"library/math/modula.hpp\"\n\n#line 2 \"library/template/template.hpp\"\
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
    \ t) {\n\tcout << (t ? \"Yes\" : \"No\") << endl;\n}\n#line 4 \"library/math/modula.hpp\"\
    \n\nll modmul(ll a, ll b, ll mod) { return __int128(a) * b % mod; }\nll modpow(ll\
    \ a, ll b, ll mod) {\n  ll ans = 1;\n  for (; b; a = modmul(a, a, mod), b /= 2)\n\
    \    if (b & 1) ans = modmul(ans, a, mod);\n  return ans;\n}\n// a^x == b (mod\
    \ p), if no such x exists than -1\nll modlog(ll a, ll b, ll p) {\n    ll n = (ll)sqrtl(p)\
    \ + 1, e = 1, f = 1, j = 1;\n    unordered_map<ll, ll> A;\n    while (j = n &&\
    \ (e = f = e * a % p) != b % p)\n        A[e * b % p] = j++;\n    if (e == b %\
    \ p) return j;\n    if (gcd(p, e) == gcd(p, b))\n        reps(i, 2, n + 2) if\
    \ (A.count(e = e * f % p)) \n            return n * i - A[e];\n    return -1;\n\
    }\n// x^2 == a (mod p)\nll modsqrt(ll a, ll p) {\n    a %= p;\n    while (a <\
    \ 0) a += p;\n    if (a == 0) return 0;\n    if (modpow(a, (p - 1) / 2, p) !=\
    \ 1) return -1;\n    if (p % 4 == 3) return modpow(a, (p + 1) / 4, p);\n    ll\
    \ s = p - 1, n = 2;\n    ll r = 0, m;\n    while (s % 2 == 0) ++r, s /= 2;\n \
    \   while (modpow(n, (p - 1) / 2, p) != p - 1) ++n;\n    ll x = modpow(a, (s +\
    \ 1) / 2, p);\n    ll b = modpow(a, s, p), g = modpow(n, s, p);\n    for (;; r\
    \ = m) {\n        ll t = b;\n        for (m = 0; m < r && t != 1; ++m) t = modmul(t,\
    \ t, p);\n        if (m == 0) return x;\n        ll gs = modpow(g, 1ll << (r -\
    \ m - 1), p);\n        g = modmul(gs, gs, p);\n        x = modmul(x, gs, p);\n\
    \        b = modmul(b, g, p);\n    }\n}\nll modinv(ll x, ll mod) { return modpow(x,\
    \ mod - 2, mod); }\n"
  code: "#pragma once\n\n#include \"../template/template.hpp\"\n\nll modmul(ll a,\
    \ ll b, ll mod) { return __int128(a) * b % mod; }\nll modpow(ll a, ll b, ll mod)\
    \ {\n  ll ans = 1;\n  for (; b; a = modmul(a, a, mod), b /= 2)\n    if (b & 1)\
    \ ans = modmul(ans, a, mod);\n  return ans;\n}\n// a^x == b (mod p), if no such\
    \ x exists than -1\nll modlog(ll a, ll b, ll p) {\n    ll n = (ll)sqrtl(p) + 1,\
    \ e = 1, f = 1, j = 1;\n    unordered_map<ll, ll> A;\n    while (j = n && (e =\
    \ f = e * a % p) != b % p)\n        A[e * b % p] = j++;\n    if (e == b % p) return\
    \ j;\n    if (gcd(p, e) == gcd(p, b))\n        reps(i, 2, n + 2) if (A.count(e\
    \ = e * f % p)) \n            return n * i - A[e];\n    return -1;\n}\n// x^2\
    \ == a (mod p)\nll modsqrt(ll a, ll p) {\n    a %= p;\n    while (a < 0) a +=\
    \ p;\n    if (a == 0) return 0;\n    if (modpow(a, (p - 1) / 2, p) != 1) return\
    \ -1;\n    if (p % 4 == 3) return modpow(a, (p + 1) / 4, p);\n    ll s = p - 1,\
    \ n = 2;\n    ll r = 0, m;\n    while (s % 2 == 0) ++r, s /= 2;\n    while (modpow(n,\
    \ (p - 1) / 2, p) != p - 1) ++n;\n    ll x = modpow(a, (s + 1) / 2, p);\n    ll\
    \ b = modpow(a, s, p), g = modpow(n, s, p);\n    for (;; r = m) {\n        ll\
    \ t = b;\n        for (m = 0; m < r && t != 1; ++m) t = modmul(t, t, p);\n   \
    \     if (m == 0) return x;\n        ll gs = modpow(g, 1ll << (r - m - 1), p);\n\
    \        g = modmul(gs, gs, p);\n        x = modmul(x, gs, p);\n        b = modmul(b,\
    \ g, p);\n    }\n}\nll modinv(ll x, ll mod) { return modpow(x, mod - 2, mod);\
    \ }"
  dependsOn:
  - library/template/template.hpp
  isVerificationFile: false
  path: library/math/modula.hpp
  requiredBy:
  - library/fps/fps.hpp
  - library/tree/FrequencyTreeDistance.hpp
  timestamp: '2025-10-31 18:20:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/yosupo/frequency-tree-distance.test.cpp
  - verify/yosupo/convolution-mod.test.cpp
documentation_of: library/math/modula.hpp
layout: document
redirect_from:
- /library/library/math/modula.hpp
- /library/library/math/modula.hpp.html
title: library/math/modula.hpp
---
