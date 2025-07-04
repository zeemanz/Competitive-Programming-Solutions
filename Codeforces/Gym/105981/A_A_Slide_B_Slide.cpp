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

        std::vector<int> dp(n + 1, m);
        dp[0] = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2 && i - j >= 0; j++) {
                dp[i + 1] = std::min(dp[i + 1], dp[i - j]);
            }
            int k = dp[i + 1];
            if (k + 1 < m && a[i] == b[k + 1]) {
                dp[i + 1] += 2;
            } else if (k < m && a[i] == b[k]) {
                dp[i + 1] += 1;
            }
        }

        if (dp[n] == m) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
