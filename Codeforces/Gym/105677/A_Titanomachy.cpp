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
struct ConvexHull : Polygon {
    using Polygon::Polygon;
    int cur = 0;
};
ConvexHull getLowerHull(std::vector<Point> p) {
    std::sort(p.begin(), p.end());
    ConvexHull lo;
    for (auto p : p) {
        while (lo.size() > 1 && toLeft(p, Line(lo.end()[-2], lo.end()[-1])) <= 0) {
            lo.pop_back();
        }
        lo.emplace_back(p);
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
        up.emplace_back(p);
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
    lhs.emplace_back(lhs[0]);
    rhs.emplace_back(rhs[0]);
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

struct Result {
    i64 sum, beg, end, ans;
    Result() : sum{}, beg{}, end{}, ans{} {}
};
Result operator+(const Result &lhs, const Result &rhs) {
    Result res;
    res.sum = lhs.sum + rhs.sum;
    res.beg = std::max(lhs.beg, lhs.sum + rhs.beg);
    res.end = std::max(rhs.end, lhs.end + rhs.sum);
    res.ans = std::max(lhs.ans, rhs.ans);
    res.ans = std::max(res.ans, lhs.end + rhs.beg);
    return res;
}
i64 queryMax(ConvexHull &p, i64 k) {
    int &i = p.cur;
    while (i + 1 < p.size() && p[i + 1].x * k + p[i + 1].y >= p[i].x * k + p[i].y) {
        i++;
    }
    return p[i].x * k + p[i].y;
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
        res.beg.emplace_back(lhs.sum + p);
    }
    res.beg = getUpperHull(res.beg);
    res.end = rhs.end;
    for (auto p : lhs.end) {
        res.end.emplace_back(p + rhs.sum);
    }
    res.end = getUpperHull(res.end);
    res.ans = lhs.ans;
    res.ans.insert(res.ans.end(), rhs.ans.begin(), rhs.ans.end());
    for (auto p : lhs.end + rhs.beg) {
        res.ans.emplace_back(p);
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

    i64 sum = 0;
    std::vector<std::pair<int, int>> itv;
    std::vector<std::pair<i64, int>> que;
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
            itv.emplace_back(l, r);
            que.emplace_back(sum, que.size());
        }
    }
    std::ranges::sort(que, std::greater());

    std::vector<std::vector<int>> query(4 << std::__lg(n));
    auto add = [&](int i) {
        auto [x, y] = itv[que[i].second];
        auto dfs = [&](auto &&self, int p, int l, int r) -> void {
            if (l >= y || r <= x) {
                return;
            }
            if (l >= x && r <= y) {
                query[p].emplace_back(i);
                return;
            }
            int m = (l + r) / 2;
            self(self, 2 * p, l, m);
            self(self, 2 * p + 1, m, r);
        };
        dfs(dfs, 1, 0, n);
    };
    for (int i = 0; i < que.size(); i++) {
        add(i);
    }

    std::vector<Result> res(que.size());
    auto work = [&](auto &&self, int p, int l, int r) -> Info {
        if (r - l == 1) {
            Info cur;
            cur.sum = Point(1, a[l]);
            cur.beg.emplace_back(cur.sum);
            cur.beg.emplace_back();
            cur.end.emplace_back(cur.sum);
            cur.end.emplace_back();
            cur.ans.emplace_back(cur.sum);
            cur.ans.emplace_back();
            for (auto j : query[p]) {
                auto [s, i] = que[j];
                res[i] = res[i] + cur.query(s);
            }
            return cur;
        }
        int m = (l + r) / 2;
        auto lhs = self(self, 2 * p, l, m);
        auto rhs = self(self, 2 * p + 1, m, r);
        auto cur = lhs + rhs;
        for (auto j : query[p]) {
            auto [s, i] = que[j];
            res[i] = res[i] + cur.query(s);
        }
        return cur;
    };
    work(work, 1, 0, n);

    for (auto res : res) {
        std::cout << res.ans << "\n";
    }

    return 0;
}
