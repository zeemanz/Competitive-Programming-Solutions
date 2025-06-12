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
        int n;
        std::cin >> n;

        std::vector<int> x;
        std::vector<std::pair<int, int>> a(n);
        for (auto &[v, p] : a) {
            std::cin >> v >> p;
            x.push_back(v);
            x.push_back(p);
        }

        std::sort(x.begin(), x.end());
        x.erase(std::unique(x.begin(), x.end()), x.end());
        for (auto &[v, p] : a) {
            v = std::lower_bound(x.begin(), x.end(), v) - x.begin();
            p = std::lower_bound(x.begin(), x.end(), p) - x.begin();
        }

        int m = x.size();
        std::vector<int> deg(2 * m);
        std::vector<std::vector<std::pair<int, int>>> adj(2 * m);
        for (int i = 0; i < n; i++) {
            auto [v, p] = a[i];
            adj[v].emplace_back(i, m + p);
            adj[m + p].emplace_back(i, v);
            deg[v]++;
            deg[m + p]++;
        }

        int s = 0;
        while (s < 2 * m && deg[s] % 2 == 0) {
            s++;
        }
        if (s == 2 * m) {
            s = 0;
            while (deg[s] == 0) {
                s++;
            }
        }

        std::vector<int> ans, vis(n), cur(2 * m);
        auto dfs = [&](auto &&self, int u) -> void {
            for (int &j = cur[u]; j < adj[u].size(); j++) {
                auto [i, v] = adj[u][j];
                if (vis[i]) {
                    continue;
                }
                vis[i] = 1;
                self(self, v);
                ans.push_back(i);
            }
        };
        dfs(dfs, s);

        if (ans.size() == n && std::count_if(deg.begin(), deg.end(), [&](int x) { return x % 2 == 1; }) <= 2) {
            std::cout << "YES\n";
            for (int i = 0; i < n; i++) {
                std::cout << ans[i] + 1 << " \n"[i == n - 1];
            }
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
