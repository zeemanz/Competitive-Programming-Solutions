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
        int n;
        std::cin >> n;

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        auto check = [&](int x) {
            std::vector<int> f(n + 1);
            for (int i = 0; i < n; i++) {
                if (i > 0) {
                    f[i] += f[i - 1];
                }
                int c = std::max(x - (n - i), 0);
                if (f[i] < c) {
                    return false;
                }
                int j = std::min(i + f[i] - c + a[i], n - 1);
                f[i + 1]++;
                f[j + 1]--;
            }
            return true;
        };

        int lo = 0, hi = n;
        while (lo < hi) {
            int m = (lo + hi + 1) / 2;
            if (check(m)) {
                lo = m;
            } else {
                hi = m - 1;
            }
        }
        std::cout << lo << "\n";
    }

    return 0;
}
