#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, m;
        std::cin >> n >> m;

        std::vector<int> h(n), s(n), d(n);
        for (int i = 0; i < n; i++) {
            std::cin >> h[i] >> s[i] >> d[i];
        }

        std::vector<std::vector<int>> c(m + 1);
        for (int i = 0; i < n; i++) {
            c[s[i]].push_back(i);
        }

        i64 ans = 0;
        for (int x = 1; x <= m; x++) {
            auto f = [&](int i) { return h[i] - 1LL * (m - x) * d[i]; };

            for (int i = 1; i <= x; i++) {
                int k = std::min(x / i, int(c[i].size()));
                std::nth_element(c[i].begin(), c[i].begin() + k, c[i].end(), [&](int i, int j) { return f(i) > f(j); });
            }

            std::vector<i64> dp(x + 1, -inf);
            dp[0] = 0;
            for (int i = 1; i <= x; i++) {
                for (int j = 0; j < x / i && j < c[i].size(); j++) {
                    for (int k = x; k >= s[c[i][j]]; k--) {
                        dp[k] = std::max(dp[k], dp[k - s[c[i][j]]] + f(c[i][j]));
                    }
                }
            }

            ans = std::max(ans, dp[x]);
        }

        std::cout << ans << "\n";
    }

    return 0;
}
