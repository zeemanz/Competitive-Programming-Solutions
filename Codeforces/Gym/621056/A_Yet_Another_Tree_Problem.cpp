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
        int n;
        std::cin >> n;

        std::vector<i64> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        std::vector<std::vector<int>> adj(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            std::cin >> u >> v;
            u--;
            v--;

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        std::vector<int> siz(n);
        std::vector dp(n, std::vector(n + 1, -inf));
        auto dfs = [&](auto &&self, int u, int p) -> void {
            dp[u][0] = 0;
            for (auto v : adj[u]) {
                if (v == p) {
                    continue;
                }
                self(self, v, u);
                auto ndp = dp[u];
                for (int x = 0; x <= siz[u]; x++) {
                    for (int y = 0; y <= siz[v]; y++) {
                        ndp[x + y] = std::max(ndp[x + y], dp[u][x] + dp[v][y]);
                    }
                }
                dp[u] = std::move(ndp);
                siz[u] += siz[v];
            }
            siz[u]++;
            dp[u][1] = std::max(dp[u][1], a[u]);
        };
        dfs(dfs, 0, -1);

        for (int k = 1; k <= n; k++) {
            dp[0][k] = std::max(dp[0][k], -1LL);
            std::cout << dp[0][k] << " \n"[k == n];
        }
    }

    return 0;
}
