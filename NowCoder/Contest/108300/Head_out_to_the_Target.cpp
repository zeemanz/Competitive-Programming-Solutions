#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    const int logn = std::__lg(n);
    std::vector par(logn + 1, std::vector(n, -1));
    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        std::cin >> par[0][i];
        par[0][i]--;
        adj[par[0][i]].push_back(i);
    }

    std::vector<int> dep(n);
    auto dfs = [&](auto &&self, int u) -> void {
        for (int i = 0; (2 << i) <= dep[u]; i++) {
            par[i + 1][u] = par[i][par[i][u]];
        }
        for (auto v : adj[u]) {
            dep[v] = dep[u] + 1;
            self(self, v);
        }
    };
    dfs(dfs, 0);

    std::vector<int> vis(n);
    vis[0] = 1;

    while (k--) {
        int u, l, r;
        std::cin >> u >> l >> r;
        u--, r++;

        if (vis[u]) {
            std::cout << l << "\n";
            return 0;
        }

        int v = u;
        for (int i = logn; i >= 0; i--) {
            if (par[i][v] != -1 && !vis[par[i][v]]) {
                v = par[i][v];
            }
        }
        if (!vis[v]) {
            v = par[0][v];
        }

        int t = l + dep[u] - dep[v];
        if (t <= r) {
            std::cout << t - 1 << "\n";
            return 0;
        }

        for (int i = logn; i >= 0; i--) {
            if (par[i][u] != -1 && l + dep[par[i][u]] - dep[v] > r) {
                u = par[i][u];
            }
        }
        if (l + dep[u] - dep[v] > r) {
            u = par[0][u];
        }

        while (u != v) {
            vis[u] = 1;
            u = par[0][u];
        }
    }

    std::cout << "-1\n";

    return 0;
}
