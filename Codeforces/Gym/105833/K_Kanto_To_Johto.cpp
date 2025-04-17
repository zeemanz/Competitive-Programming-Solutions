#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> x(m), y(m), c(m);
    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        std::cin >> x[i] >> y[i] >> c[i];
        x[i]--;
        y[i]--;
        g[x[i]].push_back(i);
        g[y[i]].push_back(i);
    }

    std::vector<int> vis(m);
    std::vector<i64> dis(n, inf);
    std::priority_queue<std::pair<i64, int>> que;
    dis[0] = 0;
    que.emplace(0, 0);
    while (!que.empty()) {
        auto [d, u] = que.top();
        que.pop();
        if (-d > dis[u]) {
            continue;
        }
        dis[u] = -d;
        for (auto i : g[u]) {
            if (vis[i]) {
                continue;
            }
            vis[i] = 1;
            auto v = u ^ x[i] ^ y[i];
            que.emplace(-(dis[u] + c[i]), v);
        }
    }

    std::vector<int> v;
    for (int i = 0; i < m; i++) {
        if (vis[i]) {
            v.push_back(c[i]);
        }
    }
    std::sort(v.begin(), v.end());

    i64 sum = 0;
    for (int i = 0; i < k && i < v.size(); i++) {
        sum += v[i];
    }
    std::cout << std::min(sum, dis[n - 1]) << "\n";

    return 0;
}
