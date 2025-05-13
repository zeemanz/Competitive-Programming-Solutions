#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<int> p(n);
        for (auto &p : p) {
            std::cin >> p;
            p--;
        }

        std::vector<int> stk, l(n), r(n);
        for (int i = 0; i < n; i++) {
            while (!stk.empty() && p[stk.back()] < p[i]) {
                r[stk.back()] = i - 1;
                stk.pop_back();
            }
            if (stk.empty()) {
                l[i] = 0;
            } else {
                l[i] = stk.back() + 1;
            }
            stk.push_back(i);
        }
        while (!stk.empty()) {
            r[stk.back()] = n - 1;
            stk.pop_back();
        }

        std::vector<int> pos(n);
        for (int i = 0; i < n; i++) {
            pos[p[i]] = i;
        }

        auto check = [&](int d) {
            auto cl = l;
            auto cr = r;
            for (int i = 0; i < n; i++) {
                cl[i] = std::max(cl[i], i - d);
                cr[i] = std::min(cr[i], i + d);
            }

            int l = std::max(pos[n - 1] - d, 0);
            int r = std::min(pos[n - 1] + d, n - 1);
            int pl = pos[n - 1];
            int pr = pos[n - 1];
            while (l > 0 || r < n - 1) {
                int nl = l, nr = r;
                for (int i = pl - 1; i >= l; i--) {
                    nl = std::min(nl, cl[i]);
                }
                for (int i = pr + 1; i <= r; i++) {
                    nr = std::max(nr, cr[i]);
                }
                if (nl == l && nr == r) {
                    return false;
                }
                pl = l;
                pr = r;
                l = nl;
                r = nr;
            }
            return true;
        };

        int lo = 0, hi = n - 1;
        while (lo < hi) {
            int m = (lo + hi) / 2;
            if (check(m)) {
                hi = m;
            } else {
                lo = m + 1;
            }
        }

        std::cout << lo << "\n";
    }

    return 0;
}
