#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    u64 dp[60][60];
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 60; j++) {
            dp[i][j] = std::numeric_limits<u64>::max() / 2;
        }
    }
    dp[0][0] = 0;

    for (int x = 1; x < 60; x++) {
        for (int i = 59; i >= 0; i--) {
            for (int j = 59; j >= 0; j--) {
                if (i >= x) {
                    dp[i][j] = std::min(dp[i][j], dp[i - x][j] + (1ULL << x));
                }
                if (j >= x) {
                    dp[i][j] = std::min(dp[i][j], dp[i][j - x] + (1ULL << x));
                }
            }
        }
    }

    int t;
    std::cin >> t;

    while (t--) {
        u64 x, y;
        std::cin >> x >> y;

        u64 ans = std::numeric_limits<u64>::max();
        for (int i = 0; i < 60; i++) {
            for (int j = 0; j < 60; j++) {
                if ((x >> i) == (y >> j)) {
                    ans = std::min(ans, dp[i][j]);
                }
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
