#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr int inf = 1E9;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--;
        v--;

        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    std::vector<int> siz(n);
    std::vector dp(n, std::vector(k + 1, 0LL));
    auto dfs = [&](auto &&self, int u, int p, int d) -> void {
        siz[u] = 1;
        for (auto [v, w] : adj[u]) {
            if (v == p) {
                continue;
            }
            self(self, v, u, d + w);
            std::vector<i64> ndp(k + 1);
            for (int i = std::min(siz[u] + siz[v], k); i >= 0; i--) {
                for (int j = std::max(i - siz[u], 0); j <= std::min(i, siz[v]); j++) {
                    i64 cur = dp[u][i - j] + dp[v][j];
                    cur += 1LL * w * (k - j) * j;
                    cur += 1LL * w * (n - k - (siz[v] - j)) * (siz[v] - j);
                    ndp[i] = std::max(ndp[i], cur);
                }
            }
            dp[u] = std::move(ndp);
            siz[u] += siz[v];
        }
    };
    dfs(dfs, 0, -1, 0);

    std::cout << dp[0][k] << "\n";

    return 0;
}
