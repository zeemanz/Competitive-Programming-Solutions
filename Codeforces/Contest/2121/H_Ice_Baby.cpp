#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

template <class Info, class Tag> struct SegmentTree {
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    SegmentTree() : n{} {}
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

struct Info {
    int x;
    Info(int x = 0) : x{x} {}
    void apply(const Tag &v) {
        x += v.x;
    }
};

Info operator+(const Info &lhs, const Info &rhs) {
    Info res;
    res.x = std::max(lhs.x, rhs.x);
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

        std::vector<std::pair<int, int>> a(n);
        for (auto &[l, r] : a) {
            std::cin >> l >> r;
            l--;
        }

        std::vector<int> v;
        for (auto [l, r] : a) {
            v.push_back(l);
            v.push_back(r);
        }

        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
        for (auto &[l, r] : a) {
            l = std::lower_bound(v.begin(), v.end(), l) - v.begin();
            r = std::lower_bound(v.begin(), v.end(), r) - v.begin();
        }

        SegmentTree<Info, Tag> seg(v.size());
        for (auto [l, r] : a) {
            seg.modify(l, seg.rangeQuery(0, l + 1));
            seg.rangeApply(l, r, {1});
            std::cout << seg.rangeQuery(0, v.size()).x << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
