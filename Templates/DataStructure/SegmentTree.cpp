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
        int res = findLast(2 * p + 1, m, r x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template <class F> int findLast(int l, int r, const F &pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};
