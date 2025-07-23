#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr int inf = 1E9;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, m;
        std::cin >> n >> m;

        std::vector<std::vector<std::pair<int, int>>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v, c;
            std::cin >> u >> v >> c;
            u--, v--;

            adj[u].emplace_back(v, c);
            adj[v].emplace_back(u, c);
        }

        std::vector<std::map<int, int>> dis(n);
        dis[0][0] = 0;

        std::deque<std::pair<int, int>> que;
        que.emplace_back(0, 0);
        while (!que.empty()) {
            auto [u, p] = que.front();
            que.pop_front();
            for (auto [v, c] : adj[u]) {
                if (dis[v].count(c)) {
                    continue;
                }
                dis[v][c] = dis[u][p] + (p != c);
                if (p == c) {
                    que.emplace_front(v, c);
                } else {
                    que.emplace_back(v, c);
                }
            }
        }

        int ans = inf;
        for (auto [k, v] : dis[n - 1]) {
            ans = std::min(ans, v);
        }

        std::cout << ans << "\n";
    }

    return 0;
}
