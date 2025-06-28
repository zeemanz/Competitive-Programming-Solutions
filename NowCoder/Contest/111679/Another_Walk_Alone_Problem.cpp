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

        std::vector<int> a(n);
        for (int i = 1; i < n; i++) {
            std::cin >> a[i];
        }

        std::vector<std::vector<std::pair<int, int>>> adj(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v, w;
            std::cin >> u >> v >> w;
            u--;
            v--;

            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }

        std::vector<int> par(n, -1);
        std::vector<i64> sum(n), min(n);
        auto dfs = [&](auto &&self, int u, int p) -> void {
            for (auto [v, w] : adj[u]) {
                if (v == p) {
                    continue;
                }
                par[v] = u;
                min[v] = min[u] + std::max(w - sum[u], 0LL);
                sum[v] = std::max(sum[u] - w, 0LL) + a[v];
                self(self, v, u);
            }
        };
        dfs(dfs, 0, -1);

        i64 res = inf;
        auto ans = min;
        for (int u = 0; u < n; u++) {
            for (auto [v, w] : adj[u]) {
                if (v == par[u]) {
                    continue;
                }
                if (a[u] + a[v] > 2 * w) {
                    i64 x = std::max({w - sum[u], 2 * w - sum[u] - a[v], 0LL});
                    res = std::min(res, min[u] + x);
                }
            }
        }

        for (int i = 1; i < n; i++) {
            ans[i] = std::min(ans[i], res);
            std::cout << ans[i] << " \n"[i + 1 == n];
        }
    }

    return 0;
}
