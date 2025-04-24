#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<Point> p(n);
    for (auto &p : p) {
        std::cin >> p;
    }

    std::sort(p.begin(), p.end(), argcmp);
    for (auto p : p) {
        std::cout << p << "\n";
    }

    return 0;
}
