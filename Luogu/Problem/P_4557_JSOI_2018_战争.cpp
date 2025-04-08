#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

using geo_t = i64;
int sgn(geo_t x) {
    if (x == 0) {
        return 0;
    } else {
        return x < 0 ? -1 : 1;
    }
}
struct Point {
    geo_t x, y;
    Point() {}
    Point(geo_t x, geo_t y) : x{x}, y{y} {}
    Point operator-() { return Point(-x, -y); }
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
    friend Point operator+(Point lhs, const Point &rhs) { return lhs += rhs; }
    friend Point operator-(Point lhs, const Point &rhs) { return lhs -= rhs; }
    friend Point operator*(Point lhs, const geo_t &rhs) { return lhs *= rhs; }
    friend Point operator*(const geo_t &lhs, Point rhs) { return rhs *= lhs; }
    friend Point operator/(Point lhs, const geo_t &rhs) { return lhs /= rhs; }
    friend Point operator/(const geo_t &lhs, Point rhs) { return rhs /= lhs; }
    friend bool operator<(const Point &lhs, const Point &rhs) {
        if (lhs.x == rhs.x) {
            return lhs.y < rhs.y;
        } else {
            return lhs.x < rhs.x;
        }
    }
    friend bool operator==(const Point &lhs, const Point &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
    friend bool operator<=(const Point &lhs, const Point &rhs) { return lhs < rhs || lhs == rhs; }
    friend std::istream &operator>>(std::istream &is, Point &rhs) { return is >> rhs.x >> rhs.y; }
    friend std::ostream &operator<<(std::ostream &os, const Point &rhs) {
        return os << "(" << rhs.x << ", " << rhs.y << ")";
    }
};
geo_t dot(Point p, Point q) { return p.x * q.x + p.y * q.y; }
geo_t cross(Point p, Point q) { return p.x * q.y - p.y * q.x; }
struct Line {
    Point a, b;
    Line() {}
    Line(Point a, Point b) : a{a}, b{b} {}
};
int toLeft(Point p, Line l) { return sgn(cross(l.b - l.a, p - l.a)); }
struct Polygon : std::vector<Point> {
    using std::vector<Point>::vector;
    Point &operator[](size_t __n) { return std::vector<Point>::operator[](__n % size()); }
    const Point &operator[](size_t __n) const { return std::vector<Point>::operator[](__n % size()); }
};
struct ConvexHull : Polygon {
    using Polygon::Polygon;
};
ConvexHull getConvexHull(std::vector<Point> p) {
    std::sort(p.begin(), p.end());
    ConvexHull lo, hi;
    for (auto p : p) {
        while (lo.size() > 1 && toLeft(p, Line(lo.end()[-2], lo.end()[-1])) <= 0) {
            lo.pop_back();
        }
        while (hi.size() > 1 && toLeft(p, Line(hi.end()[-2], hi.end()[-1])) >= 0) {
            hi.pop_back();
        }
        lo.push_back(p);
        hi.push_back(p);
    }
    std::ranges::reverse(hi);
    lo.insert(lo.end(), hi.begin() + 1, hi.end() - 1);
    return lo;
}
ConvexHull operator+(ConvexHull lhs, ConvexHull rhs) {
    lhs.push_back(lhs[0]);
    rhs.push_back(rhs[0]);
    ConvexHull res{lhs[0] + rhs[0]};
    for (int i = 0; i + 1 < lhs.size(); i++) {
        lhs[i] = lhs[i + 1] - lhs[i];
    }
    for (int i = 0; i + 1 < rhs.size(); i++) {
        rhs[i] = rhs[i + 1] - rhs[i];
    }
    lhs.pop_back();
    rhs.pop_back();
    res.resize(lhs.size() + rhs.size() + 1);
    std::ranges::merge(lhs, rhs, res.begin() + 1, [&](Point p, Point q) { return sgn(cross(p, q)) > 0; });
    res.pop_back();
    for (int i = 1; i < res.size(); i++) {
        res[i] += res[i - 1];
    }
    return getConvexHull(res);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<Point> a(n), b(m);
    for (auto &p : a) {
        std::cin >> p;
    }
    for (auto &p : b) {
        std::cin >> p;
        p = -p;
    }

    auto A = getConvexHull(a);
    auto B = getConvexHull(b);
    auto S = A + B;

    auto o = S[0];
    for (auto &p : S) {
        p -= o;
    }

    while (q--) {
        Point p;
        std::cin >> p;
        p -= o;

        auto it = std::prev(std::ranges::upper_bound(S, p, [&](Point p, Point q) {
            if (sgn(cross(p, q)) == 0) {
                return p < q;
            } else {
                return sgn(cross(p, q)) > 0;
            }
        }));
        int i = it - S.begin();

        if (sgn(cross(S[i], p)) == 0) {
            std::cout << (p <= S[i]) << "\n";
        } else {
            std::cout << (toLeft(p, Line(S[i], S[i + 1])) >= 0) << "\n";
        }
    }

    return 0;
}
