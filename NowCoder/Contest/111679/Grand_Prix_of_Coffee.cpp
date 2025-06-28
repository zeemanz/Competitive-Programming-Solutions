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

        std::vector<u32> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        u64 ans = 0;
        for (int i = 0; i < n; i++) {
            int c = 0;
            for (int j = 0; j < m; j++) {
                int ok = 1;
                if (i > 0) {
                    ok &= a[i - 1] >> j & 1;
                    if ((~a[i - 1] >> j & 1) && (a[i] >> j & 1)) {
                        ok = 0;
                    }
                }
                if (i + 1 < n) {
                    ok &= a[i + 1] >> j & 1;
                    if ((~a[i + 1] >> j & 1) && (a[i] >> j & 1)) {
                        ok = 0;
                    }
                }
                c += ok;
            }
            ans += (1 << c) - 1;
        }

        std::cout << ans << "\n";
    }

    return 0;
}
