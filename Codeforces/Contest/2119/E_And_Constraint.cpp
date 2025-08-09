#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr i64 inf = 1E18;

void solve() {
    int n;
    std::cin >> n;

    std::vector<u32> a(n + 1);
    for (int i = 1; i < n; i++) {
        std::cin >> a[i];
    }

    std::vector<u32> b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }

    auto get = [&](int i, int j) {
        u32 x = a[i] | a[i + 1] | (b[i] >> j << j);
        if (j < 31) {
            x |= 1 << j;
        }
        return x;
    };

    std::vector<i64> dp(32, inf);
    for (int i = 0; i < 32; i++) {
        u32 x = get(0, i);
        if (x >= b[0]) {
            dp[i] = x - b[0];
        }
    }
    for (int i = 1; i < n; i++) {
        std::vector<i64> ndp(32, inf);
        for (int j = 0; j < 32; j++) {
            u32 x = get(i, j);
            if (x >= b[i]) {
                for (int k = 0; k < 32; k++) {
                    u32 y = get(i - 1, k);
                    if ((x & y) == a[i]) {
                        ndp[j] = std::min(ndp[j], dp[k] + x - b[i]);
                    }
                }
            }
        }
        dp = std::move(ndp);
    }

    i64 ans = *std::min_element(dp.begin(), dp.end());
    if (ans == inf) {
        ans = -1;
    }

    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
