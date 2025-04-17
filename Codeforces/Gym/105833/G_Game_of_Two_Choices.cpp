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
    std::vector<std::vector<int>> g(n), h(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        h[v].push_back(u);
        deg[u]++;
    }

    std::vector<int> ans(n, -1);
    std::queue<int> que;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            ans[i] = 0;
            que.push(i);
        }
    }
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (auto v : h[u]) {
            deg[v]--;
            if (deg[v] == 0 && g[v].size() == 1) {
                ans[v] = ans[u] + 1;
                que.push(v);
            } else if (deg[v] == 1 && g[v].size() > 1) {
                ans[v] = ans[u] + 1;
                que.push(v);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        std::cout << ans[i] << " \n"[i == n - 1];
    }

    return 0;
}
