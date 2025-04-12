#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

template <class Info, class Tag> struct SegmentTree {
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    SegmentTree() : n{0} {}
    SegmentTree(int n, const Info &v = Info()) {
        init(n, v);
    }
    template <class T> SegmentTree(const std::vector<T> &data) {
        init(data);
    }
    void init(int n, const Info &v = Info()) {
        init(std::vector(n, v));
    }
    template <class T> void init(const std::vector<T> &data) {
        n = data.size();
        info.assign(4 << std::__lg(n), Info());
        tag.assign(4 << std::__lg(n), Tag());
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
        tag[p] = Tag();
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
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
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
        x += v.x;
    }
    friend Info operator+(const Info &lhs, const Info &rhs) {
        Info res;
        res.x = std::min(lhs.x, rhs.x);
        return res;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
        a--;
    }

    SegmentTree<Info, Tag> dp(n + 1, {inf});
    dp.modify(0, {0});

    while (k--) {
        std::vector pos(n, -1);
        std::vector ndp(n + 1, inf);
        for (int i = 0; i < n; i++) {
            dp.rangeApply(0, pos[a[i]] + 1, {i - pos[a[i]]});
            pos[a[i]] = i;
            ndp[i + 1] = dp.rangeQuery(0, i + 1).x;
        }
        dp.init(ndp);
    }

    std::cout << dp.rangeQuery(n, n + 1).x << "\n";

    return 0;
}
