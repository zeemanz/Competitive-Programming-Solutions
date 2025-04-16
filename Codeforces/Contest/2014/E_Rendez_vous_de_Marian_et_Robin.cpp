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
        int n, m, k;
        std::cin >> n >> m >> k;

        std::vector<int> h(n);
        for (int i = 0; i < k; i++) {
            int x;
            std::cin >> x;
            h[x - 1] = 1;
        }

        std::vector<std::vector<std::pair<int, int>>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v, w;
            std::cin >> u >> v >> w;
            u--;
            v--;
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }

        std::vector<i64> d1[2], dn[2];
        auto work = [&](int s, std::vector<i64> *dis) {
            for (int i = 0; i < 2; i++) {
                dis[i].assign(n, inf);
            }
            dis[0][s] = 0;
            std::priority_queue<std::array<i64, 3>> que;
            que.push({0, 0, s});
            while (!que.empty()) {
                auto [d, t, u] = que.top();
                que.pop();
                if (-d != dis[t][u]) {
                    continue;
                }
                for (auto [v, w] : adj[u]) {
                    if (t == 0) {
                        if (dis[0][v] > dis[0][u] + w) {
                            dis[0][v] = dis[0][u] + w;
                            que.push({-dis[0][v], 0, v});
                        }
                        if (h[u] && dis[1][v] > dis[0][u] + w / 2) {
                            dis[1][v] = dis[0][u] + w / 2;
                            que.push({-dis[1][v], 1, v});
                        }
                    } else {
                        if (dis[1][v] > dis[1][u] + w / 2) {
                            dis[1][v] = dis[1][u] + w / 2;
                            que.push({-dis[1][v], 1, v});
                        }
                    }
                }
            }
        };
        work(0, d1);
        work(n - 1, dn);

        i64 ans = inf;
        for (int x = 0; x < n; x++) {
            for (int a : {0, 1}) {
                for (int b : {0, 1}) {
                    ans = std::min(ans, std::max(d1[a][x], dn[b][x]));
                }
            }
        }

        if (ans == inf) {
            ans = -1;
        }
        std::cout << ans << "\n";
    }

    return 0;
}
