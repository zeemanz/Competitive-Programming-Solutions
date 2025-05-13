#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

template <class T, auto F> struct SparseTable {
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

    int n, q;
    std::cin >> n >> q;

    std::vector<u32> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    SparseTable<u32, [](u32 x, u32 y) { return x | y; }> rorq(a);
    auto get = [&](int l, int r) {
        if (l >= r) {
            return 0U;
        } else {
            return rorq(l, r);
        }
    };

    std::vector<std::vector<int>> suf(n);
    for (int i = 0; i < n; i++) {
        suf[i].emplace_back(i);
        int j = i + 1;
        while (j <= n) {
            int lo = j, hi = n;
            while (lo < hi) {
                int m = (lo + hi + 1) / 2;
                if (get(i, m) == get(i, j)) {
                    lo = m;
                } else {
                    hi = m - 1;
                }
            }
            suf[i].emplace_back(lo);
            j = lo + 1;
        }
    }

    std::vector<std::vector<int>> pre(n + 1);
    for (int i = 1; i <= n; i++) {
        pre[i].emplace_back(i);
        int j = i - 1;
        while (j >= 0) {
            int lo = 0, hi = j;
            while (lo < hi) {
                int m = (lo + hi) / 2;
                if (get(m, i) == get(j, i)) {
                    hi = m;
                } else {
                    lo = m + 1;
                }
            }
            pre[i].emplace_back(lo);
            j = lo - 1;
        }
        std::reverse(pre[i].begin(), pre[i].end());
    }

    SparseTable<u32, [](u32 x, u32 y) { return std::max(x, y); }> rmq(a);
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        l--;

        u32 ans = get(l, r);
        ans = std::max(ans, a[l] + get(l + 1, r));
        ans = std::max(ans, get(l, r - 1) + a[r - 1]);

        for (int i = 0, j = 0; i + 1 < suf[l].size(); i++) {
            auto p = suf[l][i];
            auto np = suf[l][i + 1];
            while (j + 1 < pre[r].size()) {
                auto q = pre[r][j];
                auto nq = pre[r][j + 1];
                int x = std::max(p + 1, q - 1);
                int y = std::min(np + 1, nq - 1);
                if (x < y) {
                    ans = std::max(ans, (get(l, np) | get(q, r)) + rmq(x, y));
                } else if (q - 1 >= np + 1) {
                    j = std::max(j - 1, 0);
                    break;
                }
                j++;
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
