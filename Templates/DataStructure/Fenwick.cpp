template <class T> struct Fenwick {
    int n;
    std::vector<T> a;
    Fenwick(int n = 0) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        a.assign(n, {});
    }
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    T sum(int x) {
        T res = {};
        for (int i = x; i > 0; i -= i & -i) {
            res += a[i - 1];
        }
        return res;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    int select(const T &k) {
        int res = 0;
        T cur = {};
        for (int i = 1 << std::__lg(n); i > 0; i /= 2) {
            if (res + i <= n && cur + a[res + i - 1] < k) {
                res += i;
                cur += a[res - 1];
            }
        }
        return res;
    }
};
