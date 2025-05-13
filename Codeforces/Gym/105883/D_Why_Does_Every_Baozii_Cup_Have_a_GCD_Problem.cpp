#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr i64 V = 1E7;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    std::vector<i64> lcm(4 << std::__lg(n)), sum(4 << std::__lg(n));
    auto pull = [&](int p) {
        lcm[p] = std::min(std::lcm(lcm[2 * p], lcm[2 * p + 1]), V + 1);
        sum[p] = sum[2 * p] + sum[2 * p + 1];
    };
    auto build = [&](auto &&self, int p, int l, int r) -> void {
        if (r - l == 1) {
            lcm[p] = a[l];
            sum[p] = a[l];
            return;
        }
        int m = (l + r) / 2;
        self(self, 2 * p, l, m);
        self(self, 2 * p + 1, m, r);
        pull(p);
    };
    build(build, 1, 0, n);

    auto modify = [&](auto &&self, int p, int l, int r, int x, int v) -> void {
        if (r - l == 1) {
            lcm[p] = v;
            sum[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            self(self, 2 * p, l, m, x, v);
        } else {
            self(self, 2 * p + 1, m, r, x, v);
        }
        pull(p);
    };

    auto rangeApply = [&](auto &&self, int p, int l, int r, int x, int y, int v) -> void {
        if (l >= y || r <= x) {
            return;
        }
        if (v % lcm[p] == 0) {
            return;
        }
        if (r - l == 1) {
            lcm[p] = std::gcd(lcm[p], v);
            sum[p] = lcm[p];
            return;
        }
        int m = (l + r) / 2;
        self(self, 2 * p, l, m, x, y, v);
        self(self, 2 * p + 1, m, r, x, y, v);
        pull(p);
    };

    auto rangeQuery = [&](auto &&self, int p, int l, int r, int x, int y) -> i64 {
        if (l >= y || r <= x) {
            return 0LL;
        }
        if (l >= x && r <= y) {
            return sum[p];
        }
        int m = (l + r) / 2;
        return self(self, 2 * p, l, m, x, y) + self(self, 2 * p + 1, m, r, x, y);
    };

    while (q--) {
        int o;
        std::cin >> o;

        if (o == 1) {
            int i, x;
            std::cin >> i >> x;
            i--;

            modify(modify, 1, 0, n, i, x);
        } else if (o == 2) {
            int l, r, x;
            std::cin >> l >> r >> x;
            l--;

            rangeApply(rangeApply, 1, 0, n, l, r, x);
        } else {
            int l, r;
            std::cin >> l >> r;
            l--;

            std::cout << rangeQuery(rangeQuery, 1, 0, n, l, r) << "\n";
        }
    }

    return 0;
}
