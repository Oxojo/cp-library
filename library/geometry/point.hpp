#pragma once

typedef long double ld;
constexpr ld eps = 1e-10;
constexpr ld pi = 3.1415926535897932384626L;
bool eq(ld a, ld b) { return fabs(b - a) < eps; }
int sign(ld a) { return eq(a, 0) ? 0 : a > 0 ? 1 : -1; }
struct Point {
    ld x, y;
    
    Point() = default;
    Point(ld x_, ld y_ ) : x(x_), y(y_) {}

    Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
    Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
    Point operator*(ld r) const { return {x * r, y * r}; }
    Point operator/(ld r) const { return {x / r, y / r}; }

    Point& operator+=(const Point& p) {
        x += p.x; y += p.y; return *this;
    }
    Point& operator-=(const Point& p) {
        x -= p.x; y -= p.y; return *this;
    }
    Point& operator*=(ld r) {
        x *= r; y *= r; return *this;
    }
    Point& operator/=(ld r) {
        x /= r; y /= r; return *this;
    }

    bool operator<(const Point& p) const { return !eq(x, p.x) ? x < p.x : y < p.y; }
    bool operator==(const Point& p) const { return eq(x, p.x) && eq(y, p.y); }
    bool operator!=(const Point& p) const { return !((*this) == p); }

    Point rotate(ld radian) const {
        ld c = cosl(radian), s = sinl(radian);
        return {x * c - y * s, x * s + y * c};
    }

    ld dot(const Point& p) const { return x * p.x + y * p.y; }
    ld cross(const Point& p) const { return x * p.y - y * p.x; }
    ld norm() const { return x * x + y * y; }
    ld abs() const { return sqrtl(norm()); }
    ld arg() const { return atan2l(y, x); }

    friend istream& operator>>(istream& is, Point& p) {
        return is >> p.x >> p.y;
    }
    friend ostream& operator<<(ostream& os, const Point& p) {
        return os << p.x << ' ' << p.y;
    }
};