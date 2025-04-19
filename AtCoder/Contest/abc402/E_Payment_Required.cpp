#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = double;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(12);

    int n, x;
    std::cin >> n >> x;

    std::vector<int> s(n), c(n), p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i] >> c[i] >> p[i];
    }

    std::vector dp(1 << n, std::vector<f64>(x + 1));
    for (int t = (1 << n) - 1; t >= 0; t--) {
        for (int i = 0; i < n; i++) {
            if (t >> i & 1) {
                continue;
            }
            int nt = t | 1 << i;
            for (int j = c[i]; j <= x; j++) {
                auto v = dp[t][j - c[i]] * (100 - p[i]);
                v += (dp[nt][j - c[i]] + s[i]) * p[i];
                dp[t][j] = std::max(dp[t][j], v / 100);
            }
        }
    }
    std::cout << dp[0][x] << "\n";

    return 0;
}
