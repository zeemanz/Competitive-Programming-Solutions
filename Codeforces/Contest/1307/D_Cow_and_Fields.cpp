#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> s(n);
    for (int i = 0; i < k; i++) {
        int u;
        std::cin >> u;
        u--;

        s[u] = 1;
    }

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<std::vector<int>> dis(n);
    auto work = [&](int s) {
        dis[s].assign(n, n);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> que;
        dis[s][s] = 0;
        que.emplace(0, s);
        while (!que.empty()) {
            auto [d, u] = que.top();
            que.pop();
            if (d != dis[s][u]) {
                continue;
            }
            for (auto v : adj[u]) {
                if (dis[s][v] > dis[s][u] + 1) {
                    dis[s][v] = dis[s][u] + 1;
                    que.emplace(dis[s][v], v);
                }
            }
        }
    };
    work(0);
    work(n - 1);

    std::vector<int> ord(n);
    std::iota(ord.begin(), ord.end(), 0);
    std::sort(ord.begin(), ord.end(), [&](int i, int j) {
        if (dis[0][i] == dis[0][j]) {
            return i < j;
        } else {
            return dis[0][i] < dis[0][j];
        }
    });

    std::multiset<int> suf;
    for (auto i : ord) {
        if (s[i]) {
            suf.insert(dis[n - 1][i]);
        }
    }

    int ans = 0;
    for (int i : ord) {
        if (s[i]) {
            suf.extract(dis[n - 1][i]);
            if (!suf.empty()) {
                ans = std::max(ans, dis[0][i] + *suf.rbegin() + 1);
            }
        }
    }

    std::cout << std::min(ans, dis[0][n - 1]) << "\n";

    return 0;
}
