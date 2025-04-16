#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, m;
        std::cin >> n >> m;

        std::vector<int> a(n), b(m);
        for (auto &a : a) {
            std::cin >> a;
        }
        for (auto &b : b) {
            std::cin >> b;
        }
        std::ranges::sort(a);
        std::ranges::sort(b);

        std::vector<i64> f(n / 2 + 1);
        for (int i = 0; i < n - i - 1; i++) {
            f[i + 1] = f[i] + a[n - i - 1] - a[i];
        }

        std::vector<i64> g(m / 2 + 1);
        for (int i = 0; i < m - i - 1; i++) {
            g[i + 1] = g[i] + b[m - i - 1] - b[i];
        }

        int k = 0;
        for (int x = 0; x <= std::min(n / 2, m); x++) {
            int y = std::min(n - 2 * x, (m - x) / 2);
            k = std::max(k, x + y);
        }

        std::cout << k << "\n";
        for (int i = 1; i <= k; i++) {
            int lo = std::max(2 * i - m, 0), hi = std::min(n - i, i);
            while (hi - lo + 1 > 3) {
                int a = lo + (hi - lo + 1) / 3;
                int b = hi - (hi - lo + 1) / 3;
                if (f[a] + g[i - a] > f[b] + g[i - b]) {
                    hi = b;
                } else {
                    lo = a;
                }
            }
            i64 ans = 0;
            for (int x = lo; x <= hi; x++) {
                ans = std::max(ans, f[x] + g[i - x]);
            }
            std::cout << ans << " \n"[i == k];
        }
    }

    return 0;
}
