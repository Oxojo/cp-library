// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sort_points_by_argument

#include "../../library/template/template.hpp"
#include "../../library/geometry/point.hpp"
#include "../../library/geometry/argsort.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<Point> g(n);
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }
    argsort(g);
    for (int i = 0; i < n; i++) {
        cout << (int)g[i].x << ' ' << (int)g[i].y << "\n";
    }
}