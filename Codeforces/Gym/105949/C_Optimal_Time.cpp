#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = double;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(10);

    int n, q;
    std::cin >> n >> q;

    std::vector<std::vector<int>> s(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            s[j].push_back(i);
        }
        for (int j = 2 * i; j <= n; j += i) {
            s[i].push_back(j);
        }
    }

    std::vector<f64> dp(n + 1);
    for (int t = 0; t < 100; t++) {
        std::vector<f64> ndp(n + 1);
        for (int x = 1; x <= n; x++) {
            f64 e = 0;
            for (auto y : s[x]) {
                e += dp[y - 1];
            }
            ndp[x] = std::min(dp[x - 1], e / s[x].size()) + 1;
        }
        dp = std::move(ndp);
    }

    while (q--) {
        int x;
        std::cin >> x;
        std::cout << dp[x] << "\n";
    }

    return 0;
}
