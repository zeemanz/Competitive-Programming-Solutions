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

        std::vector<std::set<int>> g(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            std::cin >> u >> v;
            u--;
            v--;
            g[u].insert(v);
            g[v].insert(u);
        }

        int s = 0;
        for (int i = 0; i < n; i++) {
            if (g[i].size() < g[s].size()) {
                s = i;
            }
        }

        std::vector<int> x, y;
        std::vector<int> conn(n);
        for (auto t : g[s]) {
            conn[t] = 1;
        }

        std::vector<int> vis(n);
        for (int i = 0; i < n; i++) {
            if (!conn[i]) {
                vis[i] = 1;
                x.push_back(i);
            } else {
                y.push_back(i);
            }
        }

        int siz = x.size();
        std::vector<int> cnt(n);
        while (!x.empty() && !y.empty()) {
            for (auto x : x) {
                for (auto y : g[x]) {
                    cnt[y]++;
                }
            }
            std::vector<int> nx, ny;
            for (auto y : y) {
                if (cnt[y] != siz) {
                    nx.push_back(y);
                } else {
                    ny.push_back(y);
                }
            }
            if (nx.empty()) {
                break;
            }
            siz += nx.size();
            x = nx;
            y = ny;
        }

        if (y.empty()) {
            std::cout << "No\n";
        } else {
            std::cout << "Yes\n";
        }
    }

    return 0;
}
