#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

template <class T, auto func> struct SparseTable {
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
                a[i + 1][j] = func(a[i][j], a[i][j + (1 << i)]);
            }
        }
    }
    T operator()(int l, int r) const {
        const int k = std::__lg(r - l);
        return func(a[k][l], a[k][r - (1 << k)]);
    }
};

constexpr i64 inf = 1000000007;

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

        SparseTable<int, [&](i64 x, i64 y) { return std::min(std::lcm(x, y), inf); }> st(a);

        std::set<i64> s;
        for (int l = 0; l < n; l++) {
            i64 x = 1;
            int r = l;
            while (r < n && x < inf) {
                int lo = r + 1, hi = n + 1;
                while (hi - lo > 1) {
                    int m = (lo + hi) / 2;
                    if (st(l, m) == x) {
                        lo = m;
                    } else {
                        hi = m;
                    }
                }
                r = lo;
                x = st(l, r);
                s.insert(x);
            }
        }

        int x = 1;
        while (s.contains(x)) {
            x++;
        }
        std::cout << x << "\n";
    }

    return 0;
}
