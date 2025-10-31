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
  bundledCode: "#line 2 \"library/math/modint.hpp\"\n\n#line 2 \"library/template/template.hpp\"\
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
    \ t) {\n\tcout << (t ? \"Yes\" : \"No\") << endl;\n}\n#line 4 \"library/math/modint.hpp\"\
    \nconst ll mod = mod2;\nstruct mint {\n\tll x;\n\tmint(ll y = 0) : x(y >= 0 ?\
    \ y % mod : (mod - (-y) % mod) % mod) {}\n\tmint &operator+=(const mint &p) {\n\
    \t\tif ((x += p.x) >= mod) x -= mod;\n\t\treturn *this;\n\t}\n\tmint &operator-=(const\
    \ mint &p) {\n\t\tif ((x += mod - p.x) >= mod) x -= mod;\n\t\treturn *this;\n\t\
    }\n\tmint &operator*=(const mint &p) {\n\t\tx = (ll)(1ll * x * p.x % mod);\n\t\
    \treturn *this;\n\t}\n\tmint &operator/=(const mint &p) {\n\t\t*this *= p.inv();\n\
    \t\treturn *this;\n\t}\n\tmint operator-() const { return mint(-x); }\n\tmint\
    \ operator+(const mint &p) const { return mint(*this) += p; }\n\tmint operator-(const\
    \ mint &p) const { return mint(*this) -= p; }\n\tmint operator*(const mint &p)\
    \ const { return mint(*this) *= p; }\n\tmint operator/(const mint &p) const {\
    \ return mint(*this) /= p; }\n\tbool operator==(const mint &p) const { return\
    \ x == p.x; }\n\tbool operator!=(const mint &p) const { return x != p.x; }\n\t\
    friend ostream &operator<<(ostream &os, const mint &p) { return os << p.x; }\n\
    \tfriend istream &operator>>(istream &is, mint &a) {\n\t\tll t; is >> t; a = mint(t);\
    \ return (is);\n\t}\n\tmint inv() const { return pow(mod - 2); }\n\tmint pow(ll\
    \ n) const {\n\t\tmint ret(1), mul(x);\n\t\twhile (n > 0) {\n\t\t\tif (n & 1)\
    \ ret *= mul;\n\t\t\tmul *= mul;\n\t\t\tn >>= 1;\n\t\t}\n\t\treturn ret;\n\t}\n\
    };\n"
  code: "#pragma once\n\n#include \"../template/template.hpp\"\nconst ll mod = mod2;\n\
    struct mint {\n\tll x;\n\tmint(ll y = 0) : x(y >= 0 ? y % mod : (mod - (-y) %\
    \ mod) % mod) {}\n\tmint &operator+=(const mint &p) {\n\t\tif ((x += p.x) >= mod)\
    \ x -= mod;\n\t\treturn *this;\n\t}\n\tmint &operator-=(const mint &p) {\n\t\t\
    if ((x += mod - p.x) >= mod) x -= mod;\n\t\treturn *this;\n\t}\n\tmint &operator*=(const\
    \ mint &p) {\n\t\tx = (ll)(1ll * x * p.x % mod);\n\t\treturn *this;\n\t}\n\tmint\
    \ &operator/=(const mint &p) {\n\t\t*this *= p.inv();\n\t\treturn *this;\n\t}\n\
    \tmint operator-() const { return mint(-x); }\n\tmint operator+(const mint &p)\
    \ const { return mint(*this) += p; }\n\tmint operator-(const mint &p) const {\
    \ return mint(*this) -= p; }\n\tmint operator*(const mint &p) const { return mint(*this)\
    \ *= p; }\n\tmint operator/(const mint &p) const { return mint(*this) /= p; }\n\
    \tbool operator==(const mint &p) const { return x == p.x; }\n\tbool operator!=(const\
    \ mint &p) const { return x != p.x; }\n\tfriend ostream &operator<<(ostream &os,\
    \ const mint &p) { return os << p.x; }\n\tfriend istream &operator>>(istream &is,\
    \ mint &a) {\n\t\tll t; is >> t; a = mint(t); return (is);\n\t}\n\tmint inv()\
    \ const { return pow(mod - 2); }\n\tmint pow(ll n) const {\n\t\tmint ret(1), mul(x);\n\
    \t\twhile (n > 0) {\n\t\t\tif (n & 1) ret *= mul;\n\t\t\tmul *= mul;\n\t\t\tn\
    \ >>= 1;\n\t\t}\n\t\treturn ret;\n\t}\n};"
  dependsOn:
  - library/template/template.hpp
  isVerificationFile: false
  path: library/math/modint.hpp
  requiredBy: []
  timestamp: '2025-10-31 18:20:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/math/modint.hpp
layout: document
redirect_from:
- /library/library/math/modint.hpp
- /library/library/math/modint.hpp.html
title: library/math/modint.hpp
---
