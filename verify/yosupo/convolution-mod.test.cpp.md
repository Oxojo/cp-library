---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/fps/fps.hpp
    title: library/fps/fps.hpp
  - icon: ':x:'
    path: library/math/modula.hpp
    title: library/math/modula.hpp
  - icon: ':question:'
    path: library/template/template.hpp
    title: library/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod
    links:
    - https://judge.yosupo.jp/problem/convolution_mod
  bundledCode: "#line 1 \"verify/yosupo/convolution-mod.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#line 2 \"library/template/template.hpp\"\
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
    \ t) {\n\tcout << (t ? \"Yes\" : \"No\") << endl;\n}\n#line 2 \"library/math/modula.hpp\"\
    \n\n#line 4 \"library/math/modula.hpp\"\n\nll modmul(ll a, ll b, ll mod) { return\
    \ __int128(a) * b % mod; }\nll modpow(ll a, ll b, ll mod) {\n  ll ans = 1;\n \
    \ for (; b; a = modmul(a, a, mod), b /= 2)\n    if (b & 1) ans = modmul(ans, a,\
    \ mod);\n  return ans;\n}\n// a^x == b (mod p), if no such x exists than -1\n\
    ll modlog(ll a, ll b, ll p) {\n    ll n = (ll)sqrtl(p) + 1, e = 1, f = 1, j =\
    \ 1;\n    unordered_map<ll, ll> A;\n    while (j = n && (e = f = e * a % p) !=\
    \ b % p)\n        A[e * b % p] = j++;\n    if (e == b % p) return j;\n    if (gcd(p,\
    \ e) == gcd(p, b))\n        reps(i, 2, n + 2) if (A.count(e = e * f % p)) \n \
    \           return n * i - A[e];\n    return -1;\n}\n// x^2 == a (mod p)\nll modsqrt(ll\
    \ a, ll p) {\n    a %= p;\n    while (a < 0) a += p;\n    if (a == 0) return 0;\n\
    \    if (modpow(a, (p - 1) / 2, p) != 1) return -1;\n    if (p % 4 == 3) return\
    \ modpow(a, (p + 1) / 4, p);\n    ll s = p - 1, n = 2;\n    ll r = 0, m;\n   \
    \ while (s % 2 == 0) ++r, s /= 2;\n    while (modpow(n, (p - 1) / 2, p) != p -\
    \ 1) ++n;\n    ll x = modpow(a, (s + 1) / 2, p);\n    ll b = modpow(a, s, p),\
    \ g = modpow(n, s, p);\n    for (;; r = m) {\n        ll t = b;\n        for (m\
    \ = 0; m < r && t != 1; ++m) t = modmul(t, t, p);\n        if (m == 0) return\
    \ x;\n        ll gs = modpow(g, 1ll << (r - m - 1), p);\n        g = modmul(gs,\
    \ gs, p);\n        x = modmul(x, gs, p);\n        b = modmul(b, g, p);\n    }\n\
    }\nll modinv(ll x, ll mod) { return modpow(x, mod - 2, mod); }\n#line 2 \"library/fps/fps.hpp\"\
    \n\n#line 5 \"library/fps/fps.hpp\"\n\ntemplate <typename T = ll>\nstruct FPS\
    \ : vector<T> {\nprivate:\n\tll mod = 998244353;\n\tll root = 3;\n\tvoid ntt(vec<T>\
    \ &a) {\n\t\tll n = sz(a), L = 31 - __builtin_clz(n);\n\t\tvl rt(2, 1);\n\t\t\
    for (ll k = 2, s = 2; k < n; k *= 2, s++) {\n\t\t\trt.resize(n);\n\t\t\tll z[]\
    \ = {1, modpow(root, mod >> s, mod)};\n\t\t\treps(i, k, 2 * k) rt[i] = modmul(rt[i\
    \ / 2], z[i & 1], mod);\n\t\t}\n\t\tvec<T> rev(n);\n\t\trep(i, n) rev[i] = (rev[i\
    \ / 2] | (i & 1) << L) / 2;\n\t\trep(i, n) if (i < rev[i]) swap(a[i], a[rev[i]]);\n\
    \t\tfor (ll k = 1; k < n; k *= 2) {\n\t\t\tfor (ll i = 0; i < n; i += 2 * k) {\n\
    \t\t\t\trep(j, k) {\n\t\t\t\t\tll z = modmul(rt[j + k], a[i + j + k], mod), &ai\
    \ = a[i + j];\n\t\t\t\t\ta[i + j + k] = ai - z + (z > ai ? mod : 0ll);\n\t\t\t\
    \t\tai += (ai + z >= mod ? z - mod : z);\n\t\t\t\t}\n\t\t\t}\n\t\t}\n\t}\n\n\t\
    vec<T> conv(vec<T> a, vec<T> b) {\n\t\tif (!sz(a) || !sz(b)) return {};\n\t\t\
    ll s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;\n\t\tll inv =\
    \ modinv(n, mod);\n\t\tvec<T> L(a), R(b), out(n);\n\t\tL.resize(n), R.resize(n);\n\
    \t\tntt(L), ntt(R);\n\t\trep(i, n) out[-i & (n - 1)] = modmul(L[i], modmul(R[i],\
    \ inv, mod), mod);\n\t\tntt(out);\n\t\tout.resize(s);\n\t\treturn out;\n\t}\n\n\
    public:\n\tusing vector<T>::vector;\n\tusing P = FPS;\n\n\tvoid set_mod(ll md,\
    \ ll g) {\n\t\tmod = md;\n\t\troot = g;\n\t}\n\t\n\tP pre(ll def) const {\n\t\t\
    return P(begin(*this), begin(*this) + min((ll)this->size(), def));\n\t}\n\tP rev(ll\
    \ deg = -1) const {\n\t\tP ret(*this);\n\t\tif (deg != -1) ret.resize(deg, T(0));\n\
    \t\treverse(all(ret));\n\t\treturn ret;\n\t}\n\n\tvoid shrink() {\n\t\twhile (this->size()\
    \ && !this->back()) this->pop_back();\n\t}\n\n\tT freq(ll p) const { return (p\
    \ < (ll)this->size()) ? (*this)[p] : T(0); }\n\n\tP operator+(const P& r) const\
    \ { return P(*this) += r; }\n\tP operator+(const T& v) const { return P(*this)\
    \ += v; }\n\tP operator-(const P& r) const { return P(*this) -= r; }\n\tP operator-(const\
    \ T& v) const { return P(*this) -= v; }\n\tP operator*(const P& r) const { return\
    \ P(*this) *= r; }\n\tP operator*(const T& v) const { return P(*this) *= v; }\n\
    \tP operator/(const P& r) const { return P(*this) /= r; }\n\tP operator%(const\
    \ P& r) const { return P(*this) %= r; }\n\n\tP& operator+=(const P& r) {\n\t\t\
    if (sz(r) > (ll)this->size()) this->resize(sz(r));\n\t\trep(i, sz(r)) (*this)[i]\
    \ += r[i];\n\t\treturn *this;\n\t}\n\tP& operator-=(const P& r) {\n\t\tif (sz(r)\
    \ > (ll)this->size()) this->resize(sz(r));\n\t\trep(i, sz(r)) (*this)[i] = (*this)[i]\
    \ - r[i] + (r[i] > (*this)[i] ? mod : 0ll);\n\t\treturn *this;\n\t}\n\n\tP& operator*=(const\
    \ P& r) {\n\t\tif (this->empty() || r.empty()) {\n\t\t\tthis->clear();\n\t\t\t\
    return *this;\n\t\t}\n\t\tauto ret = conv(*this, r);\n\t\treturn *this = {all(ret)};\n\
    \t}\n\tP& operator/=(const P& r) {\n\t\tif (this->size() < r.size()) {\n\t\t\t\
    this->clear();\n\t\t\treturn *this;\n\t\t}\n\t\tll n = this->size() - r.size()\
    \ + 1;\n\t\treturn *this = (rev().pre(n) * r.rev().inv(n)).pre(n).rev(n);\n\t\
    }\n\tP& operator%=(const P& r) {\n\t\t*this -= *this / r * r;\n\t\tshrink();\n\
    \t\treturn *this;\n\t}\n\tpair<P, P> div_mod(const P& r) {\n\t\tP q = *this /\
    \ r;\n\t\tP x = *this - q * r;\n\t\tx.shrink();\n\t\treturn make_pair(q, x);\n\
    \t}\n\tP operator-() const {\n\t\tP ret((ll)this->size());\n\t\trep(i, ll)this->size())\
    \ ret[i] = -(*this)[i];\n\t\treturn ret;\n\t}\n\tP& operator+=(const T& v) {\n\
    \t\tif (this->empty()) this->resize(1);\n\t\t(*this)[0] += v;\n\t\treturn *this;\n\
    \t}\n\tP& operator-=(const T& v) {\n\t\tif (this->empty()) this->resize(1);\n\t\
    \t(*this)[0] -= v;\n\t\treturn *this;\n\t}\n\tP& operator*=(const T& v) {\n\t\t\
    rep(i, (ll)this->size()) (*this)[i] = modmul((*this)[i], v, mod);\n\t\treturn\
    \ *this;\n\t}\n\tP dot(P r) const {\n\t\tP ret(min(this->size(), r.size()));\n\
    \t\trep(i, ret.size()) ret[i] = modmul((*this)[i], r[i], mod);\n\t\treturn ret;\n\
    \t}\n\tP operator>>(ll sz) const {\n\t\tif ((ll)this->size() <= sz) return {};\n\
    \t\tP ret(*this);\n\t\tret.erase(ret.begin(), ret.begin() + sz);\n\t\treturn ret;\n\
    \t}\n\tP operator<<(ll sz) const {\n\t\tP ret(*this);\n\t\tret.insert(ret.begin(),\
    \ sz, T(0));\n\t\treturn ret;\n\t}\n\tT operator()(T x) const {\n\t\tT r = 0,\
    \ w = 1;\n\t\tfor (auto& v : *this) {\n\t\t\tr += w * v;\n\t\t\tw *= x;\n\t\t\
    }\n\t\treturn r;\n\t}\n\tP diff() const {\n\t\tconst ll n = (ll)this->size();\n\
    \t\tP ret(max(0ll, n - 1));\n\t\treps(i, 1, n) ret[i - 1] = modmul((*this)[i],\
    \ T(i), mod);\n\t\treturn ret;\n\t}\n\tP integral() const {\n\t\tconst ll n =\
    \ (ll)this->size();\n\t\tP ret(n + 1);\n\t\trep(i, n) ret[i + 1] = modmul(freq(i),\
    \ modinv(T(i + 1), mod), mod);\n\t\treturn ret;\n\t}\n\tP inv(ll deg = -1) const\
    \ {\n\t\tif (deg == -1) deg = (ll)this->size();\n\t\tP res = P({modmul(T(1), modinv(freq(0),\
    \ mod), mod)});\n\t\tfor (ll i = 1; i < deg; i *= 2) {\n\t\t\tres = (res * T(2)\
    \ - res * res * pre(2 * i)).pre(2 * i);\n\t\t}\n\t\treturn res.pre(deg);\n\t}\n\
    \tP exp(ll n = -1) const {\n\t\tassert(freq(0) == T(0));\n\t\tif (n == -1) n =\
    \ (ll)this->size();\n\t\tP g = P({T(1)});\n\t\tfor (ll i = 1; i < n; i *= 2) {\n\
    \t\t\tg = (g * (pre(i * 2) + P({T(1)}) - g.log(i * 2))).pre(i * 2);\n\t\t}\n\t\
    \treturn g.pre(n);\n\t}\n\tP log(ll n = -1) const {\n\t\tif (n == -1) n = (ll)this->size();\n\
    \t\tassert(freq(0) == T(1));\n\t\tauto f = pre(n);\n\t\treturn (f.diff() * f.inv(n\
    \ - 1)).pre(n - 1).integral();\n\t}\n\tP sqrt(ll deg = -1) const {\n\t\tconst\
    \ ll n = (ll)this->size();\n\t\tif (deg == -1) deg = n;\n\t\tif ((*this)[0] ==\
    \ T(0)) {\n\t\t\treps(i, 1, n) {\n\t\t\t\tif ((*this)[i] != T(0)) {\n\t\t\t\t\t\
    if (i & 1) return {};\n\t\t\t\t\tif (deg - i / 2 <= 0) break;\n\t\t\t\t\tauto\
    \ ret = (*this >> i).sqrt(deg - i / 2);\n\t\t\t\t\tif (ret.empty()) return {};\n\
    \t\t\t\t\tret = ret << (i / 2);\n\t\t\t\t\tif (sz(ret) < deg) ret.resize(deg,\
    \ T(0));\n\t\t\t\t\treturn ret;\n\t\t\t\t}\n\t\t\t}\n\t\t\treturn P(deg);\n\t\t\
    }\n\t\tauto sqr = T(modsqrt((*this)[0], mod));\n\t\tif (abs(modmul(sqr, sqr, mod)\
    \ - (*this)[0]) % mod != 0) return {};\n\t\tP ret{sqr};\n\t\tT inv2 = modinv(T(2),\
    \ mod);\n\t\tfor (ll i = 1; i < deg; i <<= 1) {\n\t\t\tret = (ret + pre(i << 1)\
    \ * ret.inv(i << 1)) * inv2;\n\t\t}\n\t\treturn ret.pre(deg);\n\t}\n\tP pow(ll\
    \ k, ll n = -1) {\n\t\tif (n == -1) n = (ll)this->size();\n\t\tif (k == 0) {\n\
    \t\t\tP res(n);\n\t\t\tres[0] = T(1);\n\t\t\treturn res;\n\t\t}\n\t\trep(i, (ll)this->size())\
    \ {\n\t\t\tif ((*this)[i]) {\n\t\t\t\tT rev = modmul(T(1), modinv((*this)[i],\
    \ mod), mod);\n\t\t\t\tP ret = (((*this * rev) >> i).log(n) * T(k)).exp(n);\n\t\
    \t\t\tret *= modpow((*this)[i], k, mod);\n\t\t\t\tret = (ret << (i * k)).pre(n);\n\
    \t\t\t\tif ((ll)ret.size() < n) ret.resize(n);\n\t\t\t\treturn ret;\n\t\t\t}\n\
    \t\t\tif (__int128(i + 1) * k >= n) return P(n);\n\t\t}\n\t\treturn P(n);\n\t\
    }\n\tP pow_mod(ll n, const P& m) {\n\t\tP x = *this, r = {{1}};\n\t\twhile(n)\
    \ {\n\t\t\tif (n & 1) r = r * x % m;\n\t\t\tx = x * x % m;\n\t\t\tn >>= 1;\n\t\
    \t}\n\t\treturn r;\n\t}\n\tP shift(T c) const {\n\t\tll n = this->size();\n\t\t\
    vec<T> fact(n), rfact(n);\n\t\tfact[0] = rfact[0] = T(1);\n\t\treps(i, 1, n) fact[i]\
    \ = modmul(fact[i - 1], T(i), mod);\n\t\trfact[n - 1] = T(1) * modinv(fact[n -\
    \ 1], mod);\n\t\trrep(i, 2, n) rfact[i - 1] = modmul(rfact[i], T(i), mod);\n\t\
    \tP p(*this);\n\t\trep(i, n) p[i] = modmul(p[i], fact[i], mod);\n\t\tp = p.rev();\n\
    \t\tP bs(n, T(1));\n\t\treps(i, 1, n) bs[i] = modmul(bs[i - 1], modmul(c, modmul(rfact[i],\
    \ fact[i - 1], mod), mod), mod);\n\t\tp = (p * bs).pre(n);\n\t\tp = p.rev();\n\
    \t\trep(i, n) p[i] = modmul(p[i], rfact[i], mod);\n\t\treturn p;\n\t}\n};\n#line\
    \ 6 \"verify/yosupo/convolution-mod.test.cpp\"\n\nvoid solve() {\n    ll n, m;\
    \ cin >> n >> m;\n    FPS<ll> a(n), b(m);\n    cin >> a; cin >> b;\n    auto c\
    \ = a * b;\n    cout << c << endl;\n}\nint main() {\n    ll T = 1;\n    // cin\
    \ >> T;\n    while (T--) solve();\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#include\
    \ \"../../library/template/template.hpp\"\n#include \"../../library/math/modula.hpp\"\
    \n#include \"../../library/fps/fps.hpp\"\n\nvoid solve() {\n    ll n, m; cin >>\
    \ n >> m;\n    FPS<ll> a(n), b(m);\n    cin >> a; cin >> b;\n    auto c = a *\
    \ b;\n    cout << c << endl;\n}\nint main() {\n    ll T = 1;\n    // cin >> T;\n\
    \    while (T--) solve();\n}"
  dependsOn:
  - library/template/template.hpp
  - library/math/modula.hpp
  - library/fps/fps.hpp
  isVerificationFile: true
  path: verify/yosupo/convolution-mod.test.cpp
  requiredBy: []
  timestamp: '2025-11-01 07:23:04+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/yosupo/convolution-mod.test.cpp
layout: document
redirect_from:
- /verify/verify/yosupo/convolution-mod.test.cpp
- /verify/verify/yosupo/convolution-mod.test.cpp.html
title: verify/yosupo/convolution-mod.test.cpp
---
