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
        int n, k;
        std::cin >> n >> k;

        std::vector<std::vector<int>> adj(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            std::cin >> u >> v;
            u--;
            v--;

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        std::vector vis(2, std::vector(k, std::vector(n, -1)));
        std::vector dis(2, std::vector(k, std::vector(n, inf)));
        vis[0][0][0] = 0;
        dis[0][0][0] = 0;

        std::deque<std::array<int, 3>> que;
        que.push_back({0, 0, 0});
        while (!que.empty()) {
            auto [t, r, u] = que.front();
            que.pop_front();
            int nr = (r + 1) % k;
            int nd = dis[t][r][u] + (nr == 0);
            for (auto v : adj[u]) {
                int np = nr == 0 ? v : u;
                if (v == vis[t][r][u] || vis[0][nr][v] == np || vis[1][nr][v] != -1) {
                    continue;
                }
                for (int nt = 0; nt < 2; nt++) {
                    if (vis[nt][nr][v] == -1) {
                        vis[nt][nr][v] = np;
                        dis[nt][nr][v] = nd;
                        if (nr == 0) {
                            que.push_back({nt, nr, v});
                        } else {
                            que.push_front({nt, nr, v});
                        }
                        break;
                    }
                }
            }
        }

        std::vector<int> ans(n, inf);
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++) {
                ans[j] = std::min(ans[j], dis[i][0][j]);
            }
        }

        for (int i = 1; i < n; i++) {
            if (ans[i] == inf) {
                ans[i] = -1;
            }
            std::cout << ans[i] << " \n"[i + 1 == n];
        }
    }

    return 0;
}
