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
    i64 x, y, s;
    Info(i64 x = 0, i64 y = 0) : x{x}, y{y}, s{x - y} {}
};

Info operator+(const Info &lhs, const Info &rhs) {
    Info res;
    res.x = lhs.x + rhs.x;
    res.y = lhs.y + rhs.y;
    res.s = std::min(lhs.s, lhs.x - lhs.y + rhs.s);
    return res;
}

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n), b(n);
    for (auto &a : a) {
        std::cin >> a;
    }
    for (auto &b : b) {
        std::cin >> b;
    }

    std::vector<int> o(m + 1), x(m + 1), y(m + 1);
    std::vector<std::vector<int>> p(m + 1), adj(m + 1);
    for (int i = 1; i <= m; i++) {
        std::cin >> o[i];

        if (o[i] == 1) {
            std::cin >> x[i] >> y[i];
            x[i]--;

            adj[i - 1].push_back(i);
        } else if (o[i] == 2) {
            std::cin >> x[i] >> y[i];
            x[i]--;

            adj[i - 1].push_back(i);
        } else if (o[i] == 3) {
            int x;
            std::cin >> x;

            adj[x].push_back(i);
        } else {
            int k;
            std::cin >> k;

            p[i].resize(k);
            for (auto &p : p[i]) {
                std::cin >> p;
                p--;
            }
            p[i].push_back(n);

            adj[i - 1].push_back(i);
        }
    }

    SegmentTree<Info> seg(n);
    for (int i = 0; i < n; i++) {
        seg.modify(i, {a[i], b[i]});
    }

    std::vector<i64> ans(m + 1);
    auto dfs = [&](auto &&self, int u) -> void {
        if (o[u] == 1) {
            std::swap(a[x[u]], y[u]);
            seg.modify(x[u], {a[x[u]], b[x[u]]});
        } else if (o[u] == 2) {
            std::swap(b[x[u]], y[u]);
            seg.modify(x[u], {a[x[u]], b[x[u]]});
        } else if (o[u] == 4) {
            i64 x = 0;
            for (int l = 0; auto r : p[u]) {
                Info v = seg.rangeQuery(l, r);
                x = v.x - v.y + std::max(x, -v.s);
                if (r < n) {
                    x = (x + a[r]) / 2;
                }
                l = r + 1;
            }
            ans[u] = seg.rangeQuery(0, n).x - x;
        }
        for (auto v : adj[u]) {
            self(self, v);
        }
        if (o[u] == 1) {
            std::swap(a[x[u]], y[u]);
            seg.modify(x[u], {a[x[u]], b[x[u]]});
        } else if (o[u] == 2) {
            std::swap(b[x[u]], y[u]);
            seg.modify(x[u], {a[x[u]], b[x[u]]});
        }
    };
    dfs(dfs, 0);

    for (int i = 1; i <= m; i++) {
        if (o[i] == 4) {
            std::cout << ans[i] << " ";
        }
    }
    std::cout << "\n";
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
