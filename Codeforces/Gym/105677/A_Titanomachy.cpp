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
    Point(geo_t x = {}, geo_t y = {}) : x{x}, y{y} {}
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
    Line(Point a = {}, Point b = {}) : a{a}, b{b} {}
};
int toLeft(Point p, Line l) { return sgn(cross(l.b - l.a, p - l.a)); }
struct Polygon : std::vector<Point> {
    using std::vector<Point>::vector;
    Point &operator[](size_t __n) { return std::vector<Point>::operator[](__n % size()); }
    const Point &operator[](size_t __n) const {
        auto it = std::vector<Point>::begin();
        return std::vector<Point>::operator[](__n % size());
    }
};
using ConvexHull = Polygon;
ConvexHull getLowerHull(std::vector<Point> p) {
    std::sort(p.begin(), p.end());
    ConvexHull lo;
    for (auto p : p) {
        while (lo.size() > 1 && toLeft(p, Line(lo.end()[-2], lo.end()[-1])) <= 0) {
            lo.pop_back();
        }
        lo.push_back(p);
    }
    return lo;
}
ConvexHull getUpperHull(std::vector<Point> p) {
    std::sort(p.begin(), p.end());
    ConvexHull up;
    for (auto p : p) {
        while (up.size() > 1 && toLeft(p, Line(up.end()[-2], up.end()[-1])) >= 0) {
            up.pop_back();
        }
        up.push_back(p);
    }
    std::ranges::reverse(up);
    return up;
}
ConvexHull toConvexHull(std::vector<Point> p) {
    auto lo = getLowerHull(p);
    auto up = getUpperHull(p);
    lo.insert(lo.end(), up.begin() + 1, up.end() - 1);
    return lo;
}
ConvexHull operator+(ConvexHull lhs, ConvexHull rhs) {
    ConvexHull res{lhs[0] + rhs[0]};
    lhs.push_back(lhs[0]);
    rhs.push_back(rhs[0]);
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
    return res;
}

template <class Info, class Result> struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree(int n = 0, const Info &v = {}) { init(n, v); }
    template <class T> SegmentTree(const std::vector<T> &data) { init(data); }
    void init(int n = 0, const Info &v = {}) { init(std::vector(n, v)); }
    template <class T> void init(const std::vector<T> &data) {
        n = data.size();
        if (n == 0) {
            return;
        }
        info.assign(4 << std::__lg(n), {});
        auto build = [&](auto &&self, int p, int l, int r) -> void {
            if (r - l == 1) {
                info[p] = data[l];
                return;
            }
            int m = (l + r) / 2;
            self(self, 2 * p, l, m);
            self(self, 2 * p + 1, m, r);
            pull(p);
        };
        build(build, 1, 0, n);
    }
    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
    Result rangeQuery(int p, int l, int r, int x, int y, i64 v) {
        if (l >= y || r <= x) {
            return {};
        }
        if (l >= x && r <= y) {
            return info[p].query(v);
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y, v) + rangeQuery(2 * p + 1, m, r, x, y, v);
    }
    Result rangeQuery(int l, int r, i64 v) { return rangeQuery(1, 0, n, l, r, v); }
};
struct Result {
    i64 sum, beg, end, ans;
    Result() : sum{}, beg{}, end{}, ans{} {}
};
Result operator+(const Result &lhs, const Result &rhs) {
    Result res;
    res.sum = lhs.sum + rhs.sum;
    res.beg = std::max(lhs.beg, lhs.sum + rhs.beg);
    res.end = std::max(rhs.end, lhs.end + rhs.sum);
    res.ans = std::max({lhs.ans, rhs.ans, lhs.end + rhs.beg});
    return res;
}
i64 queryMax(const ConvexHull &p, i64 k) {
    int lo = 0, hi = p.size() - 2;
    while (lo < hi) {
        int i = (lo + hi + 1) / 2;
        if (-k * (p[i].x - p[i + 1].x) >= p[i].y - p[i + 1].y) {
            lo = i;
        } else {
            hi = i - 1;
        }
    }
    i64 res = 0;
    for (int i = lo; i <= lo + 1; i++) {
        res = std::max(res, p[i].x * k + p[i].y);
    }
    return res;
}
struct Info {
    Point sum;
    ConvexHull beg, end, ans;
    Info() : sum{}, beg{}, end{}, ans{} {}
    Result query(i64 k) {
        Result res;
        res.sum = sum.x * k + sum.y;
        res.beg = queryMax(beg, k);
        res.end = queryMax(end, k);
        res.ans = queryMax(ans, k);
        return res;
    }
};
Info operator+(const Info &lhs, const Info &rhs) {
    Info res;
    res.sum = lhs.sum + rhs.sum;
    res.beg = lhs.beg;
    for (auto p : rhs.beg) {
        res.beg.push_back(lhs.sum + p);
    }
    res.beg = getUpperHull(res.beg);
    res.end = rhs.end;
    for (auto p : lhs.end) {
        res.end.push_back(p + rhs.sum);
    }
    res.end = getUpperHull(res.end);
    res.ans = lhs.ans;
    res.ans.insert(res.ans.end(), rhs.ans.begin(), rhs.ans.end());
    for (auto p : lhs.end + rhs.beg) {
        res.ans.push_back(p);
    }
    res.ans = getUpperHull(res.ans);
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    std::vector<Info> init(n);
    for (int i = 0; i < n; i++) {
        init[i].sum = Point(1, a[i]);
        init[i].beg.push_back(init[i].sum);
        init[i].end.push_back(init[i].sum);
        init[i].ans.push_back(init[i].sum);
    }
    SegmentTree<Info, Result> seg(init);

    i64 sum = 0;
    while (q--) {
        std::string o;
        std::cin >> o;

        if (o[0] == 'S') {
            int x;
            std::cin >> x;
            sum += x;
        } else {
            int l, r;
            std::cin >> l >> r;
            l--;
            std::cout << seg.rangeQuery(l, r, sum).ans << "\n";
        }
    }

    return 0;
}
