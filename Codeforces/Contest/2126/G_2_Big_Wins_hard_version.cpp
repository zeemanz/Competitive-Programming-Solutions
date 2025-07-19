#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

template <class Info, class Tag> struct LazySegmentTree {
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    LazySegmentTree(int n = 0, const Info &v = {}) {
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
        tag.assign(4 << std::__lg(n), {});
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
    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = {};
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        push(p);
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
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        push(p);
        int m = (l + r) / 2;
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        rangeApply(1, 0, n, l, r, v);
    }
    Info query(int p, int l, int r, int x) {
        if (r - l == 1) {
            return info[p];
        }
        push(p);
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
        push(p);
        int m = (l + r) / 2;
        Info lhs = rangeQuery(2 * p, l, m, x, y);
        Info rhs = rangeQuery(2 * p + 1, m, r, x, y);
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
        push(p);
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
        push(p);
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

struct Tag {
    int x;
    Tag(int x = 0) : x{x} {}
    void apply(const Tag &v) {
        x += v.x;
    }
};

constexpr int inf = 1E9;

struct Info {
    int min, max;
    Info(int min = inf, int max = -inf) : min{min}, max{max} {}
    void apply(const Tag &v) {
        min += v.x;
        max += v.x;
    }
};

Info operator+(const Info &lhs, const Info &rhs) {
    Info res;
    res.min = std::min(lhs.min, rhs.min);
    res.max = std::max(lhs.max, rhs.max);
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        std::vector<int> stk, l(n), r(n, n);
        for (int i = 0; i < n; i++) {
            while (!stk.empty() && a[stk.back()] > a[i]) {
                r[stk.back()] = i;
                stk.pop_back();
            }
            if (!stk.empty()) {
                if (a[i] == a[stk.back()]) {
                    l[i] = l[stk.back()];
                } else {
                    l[i] = stk.back() + 1;
                }
            }
            stk.push_back(i);
        }

        std::vector<int> ord(n);
        std::iota(ord.begin(), ord.end(), 0);
        std::sort(ord.begin(), ord.end(), [&](int i, int j) { return a[i] > a[j]; });

        std::vector<int> ans(n);
        LazySegmentTree<Info, Tag> seg(n + 1);
        for (int i = 0; i <= n; i++) {
            seg.modify(i, {-i, -i});
        }
        auto dfs = [&](auto &&self, int lo, int hi, const std::vector<int> &p) -> void {
            if (hi - lo == 1) {
                for (int i : p) {
                    ans[i] = lo;
                }
                return;
            }
            int m = (lo + hi) / 2;
            for (int i = lo; i < m; i++) {
                seg.rangeApply(ord[i] + 1, n + 1, {2});
            }
            std::vector<int> a, b;
            for (int i : p) {
                if (seg.rangeQuery(i + 1, r[i] + 1).max >= seg.rangeQuery(l[i], i + 1).min) {
                    a.push_back(i);
                } else {
                    b.push_back(i);
                }
            }
            self(self, m, hi, b);
            for (int i = lo; i < m; i++) {
                seg.rangeApply(ord[i] + 1, n + 1, {-2});
            }
            self(self, lo, m, a);
        };

        std::vector<int> p(n);
        std::iota(p.begin(), p.end(), 0);
        dfs(dfs, 0, n, p);

        int max = 0;
        for (int i = 0; i < n; i++) {
            max = std::max(max, a[ord[ans[i]]] - a[i]);
        }

        std::cout << max << "\n";
    }

    return 0;
}
