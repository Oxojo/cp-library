struct Edge {
    ll from, to, cost;
    Edge (ll from, ll to, ll cost = 1ll) : from(from), to(to), cost(cost) {}
};
struct Graph {
    vector<vector<Edge>> g;
    Graph() = default;
    explicit Graph(ll n) : g(n) {}
    size_t size() const {
        return g.size();
    }
    void add(ll from, ll to, ll cost = 1ll, bool direct = 0) {
        g[from].emplace_back(from, to, cost);
        if (!direct) g[to].emplace_back(to, from, cost);
    }
    void read(ll m, ll padding = -1, bool weight = false, bool direct = false) {
        rep(i, m) {
            ll u, v; cin >> u >> v;
            u += padding; v += padding;
            ll cost = 1;
            if (weight) cin >> cost;
            add(u, v, cost, direct);
        }
    }
    vector<Edge> &operator[](const int &k) {
        return g[k];
    }
};
using Edges = vector<Edge>;