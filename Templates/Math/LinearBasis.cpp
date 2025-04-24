template <class U = u64> struct LinearBasis {
    int n, m;
    std::vector<U> a, b;
    LinearBasis() : n{0}, m{0} {}
    LinearBasis(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        this->m = 0;
        a.assign(n, {});
        b.assign(n, {});
    }
    void insert(U x) {
        U y = x;
        for (int i = n - 1; i >= 0; i--) {
            if (x >> i & 1) {
                if (a[i] == 0) {
                    a[i] = x;
                    b[i] = y;
                    m++;
                    return;
                }
                x ^= a[i];
            }
        }
    }
    bool contains(U x) {
        for (int i = n - 1; i >= 0; i--) {
            if (x >> i & 1) {
                if (a[i] == 0) {
                    return false;
                }
                x ^= a[i];
            }
        }
        return true;
    }
    int size() {
        return m;
    }
    int rank() {
        return n - m;
    }
    const U &operator[](int i) const {
        assert(0 <= i && i < n);
        return b[i];
    }
};
