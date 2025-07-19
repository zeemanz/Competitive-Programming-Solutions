#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

template <class T, T inf, class C = std::less<>> struct LiChaoSegmentTree {
    static constexpr C cmp = {};
    struct Line {
        int i;
        T k, b;
        constexpr Line(int i = std::min(-1, 1, cmp), T k = 0, T b = std::max(-inf, inf, cmp)) : i{i}, k{k}, b{b} {}
        constexpr std::pair<T, int> operator()(int x) const {
            return {k * x + b, i};
        }
    };
    struct Node {
        Node *l, *r;
        Line f;
        Node() : l{}, r{}, f{} {}
    };
    int n;
    Node *t;
    LiChaoSegmentTree(int n = 0) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        t = nullptr;
    }
    void insert(Node *&p, int l, int r, int x, int y, Line f) {
        if (l >= y || r <= x) {
            return;
        }
        if (p == nullptr) {
            p = new Node();
        }
        int m = (l + r) / 2;
        if (l >= x && r <= y) {
            if (cmp(f(m), p->f(m))) {
                std::swap(f, p->f);
            }
            if (r - l == 1) {
                return;
            }
            if (cmp(f(l), p->f(l))) {
                insert(p->l, l, m, x, y, f);
            } else {
                insert(p->r, m, r, x, y, f);
            }
        } else {
            insert(p->l, l, m, x, y, f);
            insert(p->r, m, r, x, y, f);
        }
    }
    void insert(int l, int r, Line f) {
        insert(t, 0, n, l, r, f);
    }
    void insert(Line f) {
        insert(t, 0, n, 0, n, f);
    }
    std::pair<T, int> query(Node *p, int l, int r, int x) {
        if (p == nullptr) {
            return Line()(x);
        }
        if (r - l == 1) {
            return p->f(x);
        }
        int m = (l + r) / 2;
        if (x < m) {
            return std::min(p->f(x), query(p->l, l, m, x), cmp);
        } else {
            return std::min(p->f(x), query(p->r, m, r, x), cmp);
        }
    }
    std::pair<T, int> query(int x) {
        return query(t, 0, n, x);
    }
};

struct Frac {
    i64 num, den;
    constexpr Frac(i64 x = 0) : Frac(x, 1) {}
    constexpr Frac(i64 num, i64 den) : num{num}, den{den} {
        norm();
    }
    constexpr void norm() {
        if (den < 0) {
            num = -num;
            den = -den;
        }
    }
    constexpr Frac operator-() const {
        return Frac(-num, den);
    }
    constexpr Frac &operator+=(const Frac &rhs) {
        num = num * rhs.den + rhs.num * den;
        den *= rhs.den;
        norm();
        return *this;
    }
    constexpr Frac &operator-=(const Frac &rhs) {
        return *this += -rhs;
    }
    constexpr Frac &operator*=(const Frac &rhs) {
        num *= rhs.num;
        den *= rhs.den;
        norm();
        return *this;
    }
    constexpr Frac &operator/=(const Frac &rhs) {
        num *= rhs.den;
        den *= rhs.num;
        norm();
        return *this;
    }
    friend constexpr Frac operator+(const Frac &lhs, const Frac &rhs) {
        Frac res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr Frac operator-(const Frac &lhs, const Frac &rhs) {
        Frac res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr Frac operator*(const Frac &lhs, const Frac &rhs) {
        Frac res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr Frac operator/(const Frac &lhs, const Frac &rhs) {
        Frac res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr bool operator<(const Frac &lhs, const Frac &rhs) {
        return static_cast<__int128>(lhs.num) * rhs.den < static_cast<__int128>(rhs.num) * lhs.den;
    }
    friend constexpr bool operator>(const Frac &lhs, const Frac &rhs) {
        return static_cast<__int128>(lhs.num) * rhs.den > static_cast<__int128>(rhs.num) * lhs.den;
    }
    friend std::ostream &operator<<(std::ostream &os, const Frac &rhs) {
        return os << rhs.num << "/" << rhs.den;
    }
};

constexpr int X = 39989, Y = 1E9;
constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    int ans = 0, cur = 0;
    LiChaoSegmentTree<Frac, inf, std::greater<>> seg(X + 1);

    while (q--) {
        int o;
        std::cin >> o;

        if (o == 0) {
            int x;
            std::cin >> x;
            x = (x + ans - 1) % X + 1;

            ans = -seg.query(x).second + 1;
            std::cout << ans << "\n";
        } else {
            int x0, y0, x1, y1;
            std::cin >> x0 >> y0 >> x1 >> y1;
            x0 = (x0 + ans - 1) % X + 1;
            x1 = (x1 + ans - 1) % X + 1;
            y0 = (y0 + ans - 1) % Y + 1;
            y1 = (y1 + ans - 1) % Y + 1;

            if (x0 > x1) {
                std::swap(x0, x1);
                std::swap(y0, y1);
            }

            Frac k, b;
            if (x0 == x1) {
                k = 0;
                b = std::max(y0, y1);
                seg.insert(x0, x1 + 1, {-cur, k, b});
            } else {
                k = Frac(y1 - y0, x1 - x0);
                b = y0 - k * x0;
            }

            seg.insert(x0, x1 + 1, {-cur, k, b});
            cur++;
        }
    }

    return 0;
}
