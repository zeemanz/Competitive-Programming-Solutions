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

        std::vector<std::vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            std::cin >> u >> v;
            u--;
            v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int cur = 0, cnt = 0;
        std::vector<int> dfn(n, -1), low(n), stk, bel(n, -1), siz(n);
        auto dfs = [&](auto &&self, int u, int p) -> void {
            dfn[u] = low[u] = cur++;
            stk.push_back(u);
            siz[u] = 1;
            for (auto v : adj[u]) {
                if (v == p) {
                    continue;
                }
                if (dfn[v] == -1) {
                    self(self, v, u);
                    siz[u] += siz[v];
                    low[u] = std::min(low[u], low[v]);
                } else if (bel[v] == -1) {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }
            if (dfn[u] == low[u]) {
                int v;
                do {
                    v = stk.back();
                    stk.pop_back();
                    bel[v] = cnt;
                } while (v != u);
                cnt++;
            }
        };
        dfs(dfs, 0, -1);

        auto f = [&](int n) { return 1LL * n * (n - 1) / 2; };

        i64 ans = f(n);
        for (int u = 0; u < n; u++) {
            for (auto v : adj[u]) {
                if (bel[u] != bel[v] && dfn[u] < dfn[v]) {
                    ans = std::min(ans, f(n - siz[v]) + f(siz[v]));
                }
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
