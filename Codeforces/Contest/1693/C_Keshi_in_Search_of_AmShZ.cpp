#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> deg(n);
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[v].push_back(u);
        deg[u]++;
    }

    std::vector<int> dis(n, m);
    dis[n - 1] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> que;
    que.emplace(0, n - 1);
    while (!que.empty()) {
        auto [d, u] = que.top();
        que.pop();
        if (d != dis[u]) {
            continue;
        }
        for (auto v : adj[u]) {
            if (dis[v] > dis[u] + deg[v]) {
                dis[v] = dis[u] + deg[v];
                que.emplace(dis[v], v);
            }
            deg[v]--;
        }
    }

    std::cout << dis[0] << "\n";

    return 0;
}
