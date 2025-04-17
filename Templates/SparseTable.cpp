#if __cplusplus >= 202002L
template <class T, auto F>
#else
template <class T, T (*F)(T, T)>
#endif
struct SparseTable {
    int n;
    std::vector<std::vector<T>> a;
    SparseTable(const std::vector<T> &v = {}) {
        init(v);
    }
    void init(const std::vector<T> &v) {
        n = v.size();
        const int k = std::__lg(n);
        a.assign(k + 1, std::vector<T>(n));
        for (int i = 0; i < n; i++) {
            a[0][i] = v[i];
        }
        for (int i = 0; i < k; i++) {
            for (int j = 0; j + (2 << i) <= n; j++) {
                a[i + 1][j] = F(a[i][j], a[i][j + (1 << i)]);
            }
        }
    }
    T operator()(int l, int r) const {
        assert(l < r);
        const int k = std::__lg(r - l);
        return F(a[k][l], a[k][r - (1 << k)]);
    }
};
