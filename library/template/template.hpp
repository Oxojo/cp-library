#pragma once

#include <bits/stdc++.h>
using namespace std;

// def for types
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;
using pll = pair<ll, ll>;
template <class T> using vec = vector<T>;
template <class T> using vv = vec<vec<T>>;
template <class T> using vvv = vv<vec<T>>;
using vl = vec<ll>;
using vd = vec<ld>;
using vs = vec<string>;
using vvl = vv<ll>;
template <class T> using minpq = priority_queue<T, vector<T>, greater<T>>;
using vp = vec<pll>;

// const
const ll INF = numeric_limits<ll>::max() / 4;
const ld inf = numeric_limits<ld>::max() / 2;
const ll mod1 = 1000000007;
const ll mod2 = 998244353;
const ld pi = 3.141592653589793238;

// macro
#define rep(i, r) for (ll i = 0; i < (r); i++)
#define reps(i, l, r) for (ll i = (l); i < (r); i++)
#define rrep(i, l, r) for (ll i = (r) - 1; i >= l; i--)
#define fore(e, v) for (auto &&e : v)
#define eb emplace_back
#define pb push_back
#define fi first
#define se second
#define all(a) begin(a),end(a)
#define emp(a) a.empty()
	
// func for vector
template <class T> 
ll sz(const T &t) { return (ll)t.size(); }
template <class T>
inline T vmax(const vec<T> &v) { return *max_element(all(v)); }
template <class T>
inline T vmin(const vec<T> &v) { return *min_element(all(v)); }
template <class T>
inline T Sum(const vec<T> &v) {
	return accumulate(all(v), T(0));
}
template <class T>
ll lb(const vec<T> &v, const T &a) { return lower_bound(all(v), a) - begin(v); }
template <class T>
ll ub(const vec<T> &v, const T &a) { return upper_bound(all(v), a) - begin(v); }
template <class T>
void mkuniq(T &a) { sort(all(a));	a.erase(unique(all(a)), a.end()); }
template <class T>
void mkrev(T &a) { reverse(all(a)); }
vl mkiota(ll n) { vl ret(n); iota(all(ret), 0ll); return ret; }
template <class T>
vl mkinv(vec<T> &v) {
	vl inv(vmax(v), -1);
	rep(i, sz(v)) inv[v[i]] = i;
	return inv;
}
template <class F>
vl mkorf(ll n, F f) {
	vl ord(n);
	iota(all(ord), 0ll);
	sort(all(ord), f);
	return ord;
}
template <class T>
vl mkcum(const vec<T> &v, bool rev = false) {
	vec<T> ret(sz(v) + 1);
	if (rev) {
		rrep(i, 0, sz(v)) ret[i] = v[i] + ret[i + 1];
	} else {
		rep(i, sz(v)) ret[i + 1] = ret[i] + v[i];
	}
	return ret;
}
template <class T>
bool nxp(T &v) { return next_permiutation(all(v)); }

//in-out
template <class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
	os << p.first << " " << p.second;
	return os;
}
template <class T1, class T2>
istream &operator>>(istream &is, pair<T1, T2> &p) {
	is >> p.first >> p.second;
	return is;
}
template <class T>
ostream &operator<<(ostream &os, const vec<T> &v) {
	rep(i, sz(v)) os << v[i] << " \n"[i + 1 == sz(v)];
	return os;
}
template <class T>
istream &operator>>(istream &is, vec<T> &v) {
	for (T &in : v) is >> in;
	return is;
}
istream &operator>>(istream &is, i128 &x) {
	string s; is >> s;
	x = 0;
	bool flag = 0;
	fore(c, s) {
		if (c == '-') {
			flag = true; continue;
		}
		x *= 10; x += c - '0';
	}
	if (flag) x = -x;
	return is;
}
istream &operator>>(istream &is, u128 &x) {
	string s; is >> s;
	x = 0;
	fore(c, s) {
		x *= 10; x += c - '0';
	}
	return is;
}
ostream &operator<<(ostream &os, i128 x) {
	if (x == 0) return os << 0;
	if (x < 0) os << '-', x = -x;
	string s;
	while (x) s.pb('0' + x % 10), x /= 10;
	mkrev(s);
	return os << s;
}
ostream &operator<<(ostream &os, u128 x) {
	if (x == 0) return os << 0;
	string s;
	while (x) s.pb('0' + x % 10), x /= 10;
	mkrev(s);
	return os << s;
}
void in(){}
template <class T, class... U>
void in(T &t, U &...u) {
	cin >> t;
	in(u...);
}
void out(){}
template <class T, class...U, char sep = ' '>
void out(const T &t, const U &...u) {
	cout << t;
	if (sizeof...(u)) cout << sep;
	out(u...);
}

// func for bit
ll popcnt(ll &a) { return __builtin_popcountll(a); }
inline int lsb(const ull &a) { return a ? __builtin_ctzll(a) : 64; }
inline int msb(const ull &a) { return a ? 63 - __builtin_ctzll(a) : -1; }
inline ll getbit(const ll &a, ll i) { return (a >> i) & 1; }
inline void setbit(ll &a, ll i) { a |= (1ll << i); }
inline void delbit(ll &a, ll i) { a &= ~(1ll << i); }
constexpr ll pw(ll n) { return 1ll << n; }
constexpr ll msk(ll n) { return (1ll << n) - 1; }

// func for math
template <class T>
bool btw(T a, T x, T b, bool left, bool right) {
	bool l, r;
	if (left) l = (a <= x);
	else l = (a < x);
	if (right) r = (x <= r);
	else r = (x < r);
	return l && r;
}
template <class T, class U>
T ceil(T a, U b) { return (a + b - 1) / b; }

// uncategorized
template <class T>
inline bool chmax(T &a, const T &b) { return a < b ? a = b, true : false; }
template <class T>
inline bool chmin(T &a, const T &b) { return a > b ? a = b, true : false; }
constexpr ll ten(ll n) {
	ll ret = 1, x = 10;
	for(; n; x *= x, n >>= 1) ret *= (n & 1 ? x : 1);
	return ret;
}
bool yesno(bool t) {
	cout << (t ? "Yes" : "No") << endl;
	return t;
}
template <class T>
vv<T> tramspose(const vec<T> &v) {
	if (emp(v)) return {};
	ll h = sz(v), w = sz(v[0]);
	vv<T> res(w, vec<T>(h, T()));
	rep(i, h) rep(j, w) {
		res[j][i] = v[i][j];
	}
	return res;
}
template <class T>
vv<T> rotate(const vec<T> &v, bool cw = true) {
	ll h = sz(v), w = sz(v[0]);
	vv<T> res(w, vec<T>(h, T()));
	rep(i, h) rep(j, w) {
		if (cw) res[w - 1 - j][i] = v[i][j];
		else res[j][h - 1 - i] = v[i][j];
	}
	return res;
}
template <class T>
bool sfind(set<T>&s, T key) {
	return s.find(key) != s.end();
}