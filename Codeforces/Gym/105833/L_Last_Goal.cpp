#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;

using geo_t = __int128_t;
int sgn(geo_t x) {
    if (x == 0) {
        return 0;
    } else {
        return x < 0 ? -1 : 1;
    }
}
constexpr f64 eps = 1E-9;
int sgn(f64 x) {
    if (std::fabs(x) < eps) {
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
    // friend std::ostream &operator<<(std::ostream &os, const Point &rhs) {
    //     return os << "(" << rhs.x << ", " << rhs.y << ")";
    // }
};
geo_t dot(Point p, Point q) {
    return p.x * q.x + p.y * q.y;
}
geo_t cross(Point p, Point q) {
    return p.x * q.y - p.y * q.x;
}
// 向量 OP 点乘向量 OP
geo_t square(Point p) {
    return dot(p, p);
}
// 点 P 到点 Q 的距离
geo_t distance(Point p, Point q) {
    return sqrt(square(q - p));
}
struct Line {
    Point a, b;
    Line(Point a = {}, Point b = {}) : a{a}, b{b} {}
};
int toLeft(Point p, Line l) {
    return sgn(cross(l.b - l.a, p - l.a));
}
// 直线 L 与线段 S 是否相交（严格）
bool lineCrossSegment(Line l, Line s) {
    return toLeft(s.a, l) * toLeft(s.b, l) < 0;
}
// 直线 L1 与直线 L2 的交点
std::pair<f64, f64> crossPoint(Line l1, Line l2) {
    f64 k = 1.0L * cross(l2.b - l2.a, l1.a - l2.a) / cross(l1.b - l1.a, l2.b - l2.a);
    f64 x = l1.a.x + k * (l1.b.x - l1.a.x);
    f64 y = l1.a.y + k * (l1.b.y - l1.a.y);
    return std::pair(x, y);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(11);

    std::vector<Point> p(4);
    for (auto &p : p) {
        std::cin >> p;
    }

    Point s, t;
    std::cin >> s >> t;

    if (p[1].x == p[2].x) {
        for (auto &p : p) {
            std::swap(p.x, p.y);
        }
        std::swap(s.x, s.y);
        std::swap(t.x, t.y);
    }

    auto [x, y] = crossPoint(Line(s, t), Line(p[1], p[2]));
    auto [dx, dy] = p[1] - p[2];
    if (lineCrossSegment(Line(s, t), Line(p[2], p[3]))) {
        auto q = p[2] - p[1];
        dx = q.x;
        dy = q.y;
    }

    if (sgn(x - std::min(p[1].x, p[2].x)) < 0) {
        geo_t lo = 0, hi = std::numeric_limits<geo_t>::max();
        while (lo < hi) {
            auto k = (lo + hi) / 2;
            if (sgn(x - 1.0L * k * dx - std::min(p[1].x, p[2].x)) >= 0) {
                hi = k;
            } else {
                lo = k + 1;
            }
        }
        x -= 1.0L * lo * dx;
        y -= 1.0L * lo * dy;
    } else if (sgn(x - std::max(p[1].x, p[2].x)) > 0) {
        geo_t lo = 0, hi = std::numeric_limits<geo_t>::max();
        while (lo < hi) {
            auto k = (lo + hi) / 2;
            if (sgn(x - 1.0L * k * dx - std::max(p[1].x, p[2].x)) <= 0) {
                hi = k;
            } else {
                lo = k + 1;
            }
        }
        x -= 1.0L * lo * dx;
        y -= 1.0L * lo * dy;
    }

    std::cout << std::max(std::hypot(x - p[1].x, y - p[1].y), std::hypot(x - p[2].x, y - p[2].y)) << "\n";

    return 0;
}
