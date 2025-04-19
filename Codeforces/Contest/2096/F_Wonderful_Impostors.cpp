#include <bits/stdc++.h>

using i16 = short;
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
    template <class T> LazySegmentTree(const std::vector<T> &data) {
        init(data);
    }
    void init(int n, const Info &v = {}) {
        init(std::vector(n, v));
    }
    template <class T> void init(const std::vector<T> &data) {
        n = data.size();
        info.assign(4 << std::__lg(n), {});
        tag.assign(4 << std::__lg(n), {});
        auto build = [&](auto &&self, int p, int l, int r) {
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
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return {};
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        push(p);
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
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
        return rangeApply(1, 0, n, l, r, v);
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

template <class Info> struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree(int n = 0, const Info &v = {}) {
        init(n, v);
    }
    template <class T> SegmentTree(const std::vector<T> &data) {
        init(data);
    }
    void init(int n, const Info &v = {}) {
        init(std::vector(n, v));
    }
    template <class T> void init(const std::vector<T> &data) {
        n = data.size();
        info.assign(4 << std::__lg(n), {});
        auto build = [&](auto &&self, int p, int l, int r) {
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
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return {};
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
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
    int x;
    Info(int x = inf) : x{x} {}
    void apply(const Tag &v) {
        x = std::max(x + v.x, 0);
    }
};

Info operator+(const Info &lhs, const Info &rhs) {
    Info res;
    res.x = std::min(lhs.x, rhs.x);
    return res;
}

template <class T, class Cmp = std::less<T>> struct ErasableHeap {
    std::priority_queue<T, std::vector<T>, Cmp> heap, trash;
    ErasableHeap() {}
    ErasableHeap(const std::vector<T> &data) : heap{data.begin(), data.end()} {}
    void push(const T &x) {
        heap.push(x);
    }
    void pop() {
        doErase();
        heap.pop();
    }
    const T &top() {
        doErase();
        return heap.top();
    }
    void erase(const T &x) {
        trash.push(x);
    }
    void doErase() {
        while (!heap.empty() && !trash.empty() && heap.top() == trash.top()) {
            heap.pop();
            trash.pop();
        }
    }
    bool empty() const {
        return heap.size() == trash.size();
    }
};

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::array<int, 3>> s(m);
    for (auto &[o, l, r] : s) {
        std::cin >> o >> l >> r;
        l--;
    }

    std::vector<ErasableHeap<int, std::greater<>>> que(n);
    for (int i = 0; i < n; i++) {
        que[i].push(inf);
    }

    SegmentTree<Info> seg(n);
    auto modify = [&](int x, int v) {
        if (v > 0) {
            que[x].push(v);
        } else {
            que[x].erase(-v);
        }
        seg.modify(x, {que[x].top()});
    };

    LazySegmentTree<Info, Tag> cover(n, {0});
    auto check = [&](int i) {
        auto [o, l, r] = s[i];
        if (o == 0) {
            int x = cover.findLast(0, l, [&](const Info &v) { return v.x == 0; }) + 1;
            int y = cover.findFirst(r, n, [&](const Info &v) { return v.x == 0; });
            if (y == -1) {
                y = n;
            }
            return seg.rangeQuery(x, y).x > y;
        } else {
            return cover.rangeQuery(l, r).x == 0;
        }
    };
    auto insert = [&](int i) {
        auto [o, l, r] = s[i];
        if (o == 0) {
            cover.rangeApply(l, r, {1});
        } else {
            modify(l, r);
        }
    };
    auto erase = [&](int i) {
        auto [o, l, r] = s[i];
        if (o == 0) {
            cover.rangeApply(l, r, {-1});
        } else {
            modify(l, -r);
        }
    };

    std::vector<int> left(m + 1);
    for (int r = 1; r <= m; r++) {
        left[r] = left[r - 1];
        while (!check(r - 1)) {
            erase(left[r]);
            left[r]++;
        }
        insert(r - 1);
    }

    int q;
    std::cin >> q;

    while (q--) {
        int l, r;
        std::cin >> l >> r;
        l--;

        if (left[r] <= l) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
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
