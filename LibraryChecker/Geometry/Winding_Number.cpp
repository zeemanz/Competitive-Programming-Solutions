#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = double;

const f64 pi = std::acos(-1.0), eps = 1E-9;

f64 rad2deg(f64 rad) {
    return 180 / pi * rad;
}
f64 deg2rad(f64 deg) {
    return pi / 180 * deg;
}

using geo_t = i64;

int sgn(geo_t x) {
    if (x == 0) {
        return x;
    } else {
        return x < 0 ? -1 : 1;
    }
}

struct Point {
    geo_t x, y;
    Point(geo_t x = 0, geo_t y = 0) : x{x}, y{y} {}
    Point operator-() const {
        return Point(-x, -y);
    }
    Point &operator+=(const Point &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Point &operator-=(const Point &rhs) {
        return *this += -rhs;
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
        lhs += rhs;
        return lhs;
    }
    friend Point operator-(Point lhs, const Point &rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend Point operator*(Point lhs, const geo_t &rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend Point operator*(const geo_t &lhs, Point rhs) {
        rhs *= lhs;
        return rhs;
    }
    friend Point operator/(Point lhs, const geo_t &rhs) {
        lhs /= rhs;
        return lhs;
    }
    friend bool operator<(const Point &lhs, const Point &rhs) {
        if (sgn(lhs.x - rhs.x) == 0) {
            return sgn(lhs.y - rhs.y) < 0;
        } else {
            return sgn(lhs.x - rhs.x) < 0;
        }
    }
    friend bool operator==(const Point &lhs, const Point &rhs) {
        return sgn(lhs.x - rhs.x) == 0 && sgn(lhs.y - rhs.y) == 0;
    }
    friend std::istream &operator>>(std::istream &is, Point &rhs) {
        return is >> rhs.x >> rhs.y;
    }
    friend std::ostream &operator<<(std::ostream &os, const Point &rhs) {
        return os << rhs.x << " " << rhs.y;
    }
};

geo_t dot(Point p, Point q) {
    return p.x * q.x + p.y * q.y;
}
geo_t cross(Point p, Point q) {
    return p.x * q.y - p.y * q.x;
}
bool argcmp(Point p, Point q) {
    auto quad = [&](Point p) {
        if (sgn(p.y) < 0) {
            return 1;
        } else if (sgn(p.y) > 0) {
            return 4;
        } else {
            if (sgn(p.x) < 0) {
                return 5;
            } else if (sgn(p.x) > 0) {
                return 3;
            } else {
                return 2;
            }
        }
    };
    if (quad(p) == quad(q)) {
        return sgn(cross(p, q)) > 0;
    } else {
        return quad(p) < quad(q);
    }
}
geo_t square(Point p) {
    return dot(p, p);
}
f64 length(Point p) {
    return std::sqrt(square(p));
}
f64 distance(Point p, Point q) {
    return std::sqrt(square(q - p));
}
f64 radian(Point p, Point q) {
    return std::acos(dot(p, q) / length(p) / length(q));
}
f64 degree(Point p, Point q) {
    return rad2deg(radian(p, q));
}
geo_t area(Point p, Point q, Point o = Point()) {
    return cross(p - o, q - o);
}
Point rotate(Point p, Point o = Point()) {
    Point v = p - o;
    return o + Point(-v.y, v.x);
}
Point rotate(Point p, f64 s, f64 c, Point o = Point()) {
    Point v = p - o;
    return o + Point(v.x * c - v.y * s, v.x * s + v.y * c);
}
Point rotate(Point p, f64 rad, Point o = Point()) {
    f64 s = std::sin(rad), c = std::cos(rad);
    return rotate(p, s, c, o);
}
Point format(Point p) {
    return p / length(p);
}
Point norm(Point p) {
    return rotate(format(p));
}

struct Line {
    Point a, b;
    Line(Point a = Point(), Point b = Point()) : a{a}, b{b} {}
};

// -1: 右侧
//  0: 线上
//  1: 左侧
int toLeft(Point p, Line l) {
    return sgn(cross(l.b - l.a, p - l.a));
}
bool onSegment(Point p, Line s) {
    if (toLeft(p, s) != 0) {
        return false;
    } else {
        if (sgn(std::min(s.a.x, s.b.x) - p.x) <= 0 && sgn(p.x - std::max(s.a.x, s.b.x)) <= 0) {
            return sgn(std::min(s.a.y, s.b.y) - p.y) <= 0 && sgn(p.y - std::max(s.a.y, s.b.y)) <= 0;
        } else {
            return false;
        }
    }
}
f64 distance(Point p, Line l) {
    return std::fabs(cross(l.b - l.a, p - l.a) / length(l.b - l.a));
}
f64 distance2Segment(Point p, Line s) {
    if (s.a == s.b) {
        return length(p - s.a);
    } else {
        if (sgn(dot(s.b - s.a, p - s.a)) < 0) {
            return length(p - s.a);
        } else if (sgn(dot(s.a - s.b, p - s.b)) < 0) {
            return length(p - s.b);
        } else {
            return distance(p, s);
        }
    }
}
Point project(Point p, Line l) {
    return l.a + (l.b - l.a) * dot(l.b - l.a, p - l.a) / square(l.b - l.a);
}
bool parallel(Line l1, Line l2) {
    return sgn(cross(l1.b - l1.a, l2.b - l2.a)) == 0;
}
// 0: 不相交
// 1: 正规相交
// 2: 端点相交
int segmentCrossSegment(Line s1, Line s2) {
    if (onSegment(s1.a, s2) || onSegment(s1.b, s2) || onSegment(s2.a, s1) || onSegment(s2.b, s1)) {
        return 2;
    } else {
        return toLeft(s1.a, s2) != toLeft(s1.b, s2) && toLeft(s2.a, s1) != toLeft(s2.b, s1);
    }
}
// 0: 不相交
// 1: 正规相交
// 2: 端点相交
// 3: 重合
int lineCrossSegment(Line l, Line s) {
    if (toLeft(s.a, l) == 0 && toLeft(s.b, l) == 0) {
        return 3;
    } else if (toLeft(s.a, l) == 0 || toLeft(s.b, l) == 0) {
        return 2;
    } else {
        return toLeft(s.a, l) != toLeft(s.b, l);
    }
}
// 0: 平行
// 1: 相交
// 2: 重合
int lineCrossLine(Line l1, Line l2) {
    if (parallel(l1, l2)) {
        if (toLeft(l1.a, l2) == 0) {
            return 2;
        } else {
            return 0;
        }
    } else {
        return 1;
    }
}
Point crossPoint(Line l1, Line l2) {
    f64 k = cross(l2.b - l2.a, l1.a - l2.a) / cross(l1.b - l1.a, l2.b - l2.a);
    return l1.a + k * (l1.b - l1.a);
}

struct Polygon : std::vector<Point> {
    using vector::vector;
    Polygon(const std::vector<Point> &p) : vector(p) {}
    Point &operator[](size_t __n) {
        return std::vector<Point>::operator[](__n % size());
    }
    const Point &operator[](size_t __n) const {
        return std::vector<Point>::operator[](__n % size());
    }
};

// 两倍面积
geo_t area(const Polygon &poly) {
    geo_t res = 0;
    for (int i = 0; i < poly.size(); i++) {
        res += cross(poly[i], poly[i + 1]);
    }
    return res;
}
bool clockwise(const Polygon &poly) {
    return area(poly) < 0;
}
int windingNumber(Point p, const Polygon &poly) {
    int res = 0;
    for (int i = 0; i < poly.size(); i++) {
        if (onSegment(p, {poly[i], poly[i + 1]})) {
            return std::numeric_limits<int>::max();
        }
        if (sgn(poly[i].y - p.y) <= 0) {
            if (sgn(poly[i + 1].y - p.y) > 0) {
                if (toLeft(p, {poly[i], poly[i + 1]}) == 1) {
                    res++;
                }
            }
        } else {
            if (sgn(poly[i + 1].y - p.y) <= 0) {
                if (toLeft(p, {poly[i], poly[i + 1]}) == -1) {
                    res--;
                }
            }
        }
    }
    return res;
}
// 0: 外部
// 1: 内部
// 2: 边界
int inPolygon(Point p, const Polygon &poly) {
    int res = windingNumber(p, poly);
    if (res == std::numeric_limits<int>::max()) {
        return 2;
    } else {
        return res != 0;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<Point> p(n);
    for (auto &p : p) {
        std::cin >> p;
    }

    int m;
    std::cin >> m;

    while (m--) {
        Point q;
        std::cin >> q;

        int res = windingNumber(q, p);
        if (res == std::numeric_limits<int>::max()) {
            std::cout << "EDGE\n";
        } else {
            std::cout << res << "\n";
        }
    }

    return 0;
}
