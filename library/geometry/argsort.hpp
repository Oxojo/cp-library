#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "./point.hpp"

// sort points by argument in [-pi, pi)
inline void argsort(vector<Point>& g) {
    auto half = [](const Point& p) {
        if (p.y < -eps) return 0;
        if (p.y > eps) return 2;
        if (p.x < -eps) return 3;
        return 1;
    };
    sort(g.begin(), g.end(), [&](const Point& a, const Point& b) {
        int ha = half(a), hb = half(b);
        if (ha != hb) return ha < hb;
        return sign(a.cross(b)) > 0;
    });
}
