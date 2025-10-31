#include <bits/stdc++.h>
using namespace std;
#define MM << ' ' <<
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using vl = vector<ll>;
template <class T> using vec = vector<T>;
template <class T> using vv = vec<vec<T>>;
template <class T> using vvv = vv<vec<T>>;
template <class T> using minpq = priority_queue<T, vector<T>, greater<T>>;
#define rep(i, r) for(ll i = 0; i < (r); i++)
#define reps(i, l, r) for(ll i = (l); i < (r); i++)
#define rrep(i, l, r) for(ll i = (r) - 1; i >= l; i--)
template <class T> void uniq(T &a) { sort(all(a)); erase(unique(all(a)), a.end()); }
#define all(a) (a).begin(), (a).end()
#define sz(a) (ll)(a).size()
const ll INF = numeric_limits<ll>::max() / 4;
const ld inf = numeric_limits<ld>::max() / 2;
const ll mod1 = 1000000007;
const ll mod2 = 998244353;
const ld pi = 3.141592653589793238;
template <class T> void rev(T &a) { reverse(all(a)); }
ll popcnt(ll a) { return __builtin_popcountll(a); }
template<typename T>
bool chmax(T &a, const T& b) { return a < b ? a = b, true : false; }
template<typename T>
bool chmin(T &a, const T& b) { return a > b ? a = b, true : false; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) {
	os << p.first << " " << p.second;
	return os;
}
template <typename T1, typename T2>
istream& operator>>(istream& is, pair<T1, T2>& p) {
	is >> p.first >> p.second;
	return is;
}
template <typename T>
ostream& operator<<(ostream& os, const vec<T>& v) {
	rep(i, sz(v)) {
		os << v[i] << " \n"[i + 1 == sz(v)];
	}
	return os;
}
template <typename T>
istream& operator>>(istream& is, vec<T>& v) {
	for (T& in : v) is >> in;
	return is;
}
void yesno(bool t) {
	cout << (t ? "Yes" : "No") << endl;
}