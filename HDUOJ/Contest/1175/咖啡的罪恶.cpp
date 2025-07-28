#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

template <class Info> struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree(int n = 0, const Info &v = {}) {
        init(n, v);
    }
    void init(int n, const Info &v = {}) {
        init(std::vector(n, v));
    }
    void init(const std::vector<Info> &a) {
        n = a.size();
        if (n == 0) {
            return;
        }
        info.assign(4 << std::__lg(n), {});
        auto dfs = [&](auto &&self, int p, int l, int r) -> void {
            if (r - l == 1) {
                info[p] = a[l];
                return;
            }
            int m = (l + r) / 2;
            self(self, 2 * p, l, m);
            self(self, 2 * p + 1, m, r);
            pull(p);
        };
        dfs(dfs, 1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int x, const Info &v) {
        modify(1, 0, n, x, v);
    }
    Info query(int p, int l, int r, int x) {
        if (r - l == 1) {
            return info[p];
        }
        int m = (l + r) / 2;
        if (x < m) {
            return query(2 * p, l, m, x);
        } else {
            return query(2 * p + 1, m, r, x);
        }
    }
    Info query(int x) {
        return query(1, 0, n, x);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return {};
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        auto lhs = rangeQuery(2 * p, l, m, x, y);
        auto rhs = rangeQuery(2 * p + 1, m, r, x, y);
        return lhs + rhs;
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    template <class F> int findFirst(int p, int l, int r, int x, int y, const F &pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template <class F> int findFirst(int l, int r, const F &pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template <class F> int findLast(int p, int l, int r, int x, int y, const F &pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template <class F> int findLast(int l, int r, const F &pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};

struct Info {
    int len;
    Info(int len = 0) : len{len} {}
};

Info operator+(const Info &lhs, const Info &rhs) {
    Info res;
    res.len = std::max(lhs.len, rhs.len);
    return res;
}

void solve() {
    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    std::set<int> pos = {-1, n};
    auto prev = [&](int i) { return *std::prev(pos.lower_bound(i)); };
    auto next = [&](int i) { return *pos.upper_bound(i); };
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            pos.insert(i);
        }
    }

    SegmentTree<Info> seg(n);
    auto insert = [&](int p) {
        if (a[p] == 0) {
            p = prev(p);
        } else {
            pos.insert(p);
        }
        for (int t = 0; t < 4 && p >= 0; t++, p = prev(p)) {
            if (p + 4 <= n) {
                if (a[p] == 1 && a[p + 1] == 2 && a[p + 2] == 1 && a[p + 3] == 0) {
                    seg.modify(p, {4});
                } else if (a[p] == 2 && a[p + 1] == 0 && a[p + 2] == 2 && a[p + 3] == 0) {
                    seg.modify(p, {4});
                }
            }
            if (p + 5 <= n) {
                if (a[p] == 2 && a[p + 1] == 1 && a[p + 2] == 2 && a[p + 3] == 0 && a[p + 4] == 0) {
                    seg.modify(p, {5});
                }
            }
            if (a[p] >= 3 && p + a[p] + 4 <= n) {
                if (a[p + 1] == 2 && a[p + 2] == 1) {
                    if (next(p + 2) == p + a[p] && a[p + a[p]] == 1 && next(p + a[p]) >= p + a[p] + 4) {
                        seg.modify(p, {a[p] + 4});
                    }
                }
            }
        }
    };
    auto erase = [&](int p) {
        int q = p;
        if (a[q] == 0) {
            q = prev(q);
        }
        for (int t = 0; t < 4 && q >= 0; t++, q = prev(q)) {
            if (q + seg.query(q).len > p) {
                seg.modify(q, {0});
            }
        }
        if (a[p] > 0) {
            pos.erase(p);
        }
    };
    for (int i = 0; i < n; i++) {
        insert(i);
    }

    while (q--) {
        int o;
        std::cin >> o;

        if (o == 1) {
            int p, x;
            std::cin >> p >> x;
            p--;

            if (a[p] != x) {
                erase(p);
                a[p] = x;
                insert(p);
            }
        } else {
            int l, r;
            std::cin >> l >> r;
            l--;

            int m = prev(r), ans = 0;
            for (int t = 0; t < 4 && m >= l; t++, m = prev(m)) {
                Info v = seg.query(m);
                if (m + v.len <= r) {
                    ans = std::max(ans, v.len);
                }
            }

            std::cout << std::max(ans, seg.rangeQuery(l, m + 1).len) << "\n";
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
