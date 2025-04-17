#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = double;
using f80 = long double;

using geo_t = f80;
constexpr geo_t eps = 1E-18;
int sgn(geo_t x) {
    if (x == 0) {
        return 0;
    } else {
        return x < 0 ? -1 : 1;
    }
}
struct Point {
    geo_t x, y;
    Point(geo_t x = {}, geo_t y = {}) : x{x}, y{y} {}
    Point operator-() {
        return Point(-x, -y);
    }
    Point &operator+=(const Point &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Point &operator-=(const Point &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    Point &operator*=(const geo_t &rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }
    Point &operator/=(const geo_t &rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }
    friend Point operator+(Point lhs, const Point &rhs) {
        return lhs += rhs;
    }
    friend Point operator-(Point lhs, const Point &rhs) {
        return lhs -= rhs;
    }
    friend Point operator*(Point lhs, const geo_t &rhs) {
        return lhs *= rhs;
    }
    friend Point operator*(const geo_t &lhs, Point rhs) {
        return rhs *= lhs;
    }
    friend Point operator/(Point lhs, const geo_t &rhs) {
        return lhs /= rhs;
    }
    friend Point operator/(const geo_t &lhs, Point rhs) {
        return rhs /= lhs;
    }
    friend bool operator<(const Point &lhs, const Point &rhs) {
        if (lhs.x == rhs.x) {
            return lhs.y < rhs.y;
        } else {
            return lhs.x < rhs.x;
        }
    }
    friend bool operator==(const Point &lhs, const Point &rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
    friend bool operator<=(const Point &lhs, const Point &rhs) {
        return lhs < rhs || lhs == rhs;
    }
    friend std::istream &operator>>(std::istream &is, Point &rhs) {
        int x, y;
        is >> x >> y;
        rhs = Point(x, y);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Point &rhs) {
        return os << "(" << rhs.x << ", " << rhs.y << ")";
    }
};
geo_t dot(Point p, Point q) {
    return p.x * q.x + p.y * q.y;
}
geo_t cross(Point p, Point q) {
    return p.x * q.y - p.y * q.x;
}
geo_t square(Point p) {
    return dot(p, p);
}
geo_t distance(Point p, Point q) {
    return std::sqrt(square(q - p));
}
struct Line {
    Point a, b;
    Line(Point a = {}, Point b = {}) : a{a}, b{b} {}
};
int toLeft(Point p, Line l) {
    return sgn(cross(l.b - l.a, p - l.a));
}
Point crossPoint(Line l1, Line l2) {
    geo_t k = cross(l2.b - l2.a, l1.a - l2.a) / cross(l1.b - l1.a, l2.b - l2.a);
    return l1.a + k * (l1.b - l1.a);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(11);

    std::vector<Point> p(4);
    for (int i = 0; i < 4; i++) {
        std::cin >> p[i];
    }

    Point s, t;
    std::cin >> s >> t;

    auto o = crossPoint(Line(s, t), Line(p[1], p[2]));
    auto x = distance(p[1], o);
    auto d = distance(p[1], p[2]);
    x = std::fmod(x, d);
    std::cout << std::max(x, d - x) << "\n";

    return 0;
}
