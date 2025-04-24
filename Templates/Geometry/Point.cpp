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
geo_t area(Point p, Point q, Point o = {}) {
    return cross(p - o, q - o);
}
Point rotate(Point p, Point o = {}) {
    Point v = p - o;
    return o + Point(-v.y, v.x);
}
Point rotate(Point p, f64 s, f64 c, Point o = {}) {
    Point v = p - o;
    return o + Point(v.x * c - v.y * s, v.x * s + v.y * c);
}
Point rotate(Point p, f64 rad, Point o = {}) {
    f64 s = std::sin(rad), c = std::cos(rad);
    return rotate(p, s, c, o);
}
Point format(Point p) {
    return p / length(p);
}
Point norm(Point p) {
    return rotate(format(p));
}
