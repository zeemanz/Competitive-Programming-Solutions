#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

using geo_t = long long;
using f64 = long double;

const f64 pi = acosl(-1), eps = 1E-9;

template <class T> int sgn(T x) {
    if (std::abs(x) < eps) {
        return 0;
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
f64 radian(Point p, Point q) {
    f64 rad = atan2l(q.y, q.x) - atan2(p.y, p.x);
    return rad;
}
geo_t area(Point p, Point q, Point o = {}) {
    return cross(p - o, q - o);
}

void solve() {
    int n;
    Point o;
    std::cin >> n >> o;

    std::vector<Point> p(n);
    for (auto &p : p) {
        std::cin >> p;
    }

    bool out = false;
    for (int i = 0; i < n; i++) {
        out |= area(p[i], p[(i + 1) % n], o) < 0;
    }

    f64 ans = 0;
    if (!out) {
        i64 max = 0;
        for (auto p : p) {
            max = std::max(max, square(p - o));
        }
        std::vector<Point> q;
        for (auto p : p) {
            if (square(p - o) == max) {
                q.push_back(p - o);
            }
        }
        for (int i = 0; i < q.size(); i++) {
            auto rad = radian(q[i], q[(i + 1) % q.size()]);
            if (sgn(rad) <= 0) {
                rad += 2 * pi;
            }
            ans = std::max(ans, rad);
        }
    } else {
        ans = 2 * pi;
    }

    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(15);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
