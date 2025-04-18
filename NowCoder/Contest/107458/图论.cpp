#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<int> vis(n);
    for (int i = 0; i < m; i++) {
        int x;
        std::cin >> x;
        vis[x - 1] = 1;
    }

    std::vector<std::pair<int, int>> ans;
    auto dfs = [&](auto &&self, int u, int p) -> int {
        std::vector<int> cur;
        for (auto v : g[u]) {
            if (v == p) {
                continue;
            }
            int res = self(self, v, u);
            if (res == 1) {
                cur.push_back(v);
            }
        }
        if (!vis[u]) {
            while (cur.size() > 1) {
                int v = cur.back();
                cur.pop_back();
                ans.emplace_back(u, v);
            }
            return cur.size() > 0;
        } else {
            for (auto v : cur) {
                ans.emplace_back(u, v);
            }
            return 1;
        }
    };
    dfs(dfs, 0, -1);

    std::cout << ans.size() << "\n";
    for (auto [u, v] : ans) {
        std::cout << u + 1 << " " << v + 1 << "\n";
    }

    return 0;
}
