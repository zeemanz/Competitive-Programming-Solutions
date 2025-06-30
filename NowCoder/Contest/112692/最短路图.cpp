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

        std::vector<int> w(m);
        for (auto &w : w) {
            std::cin >> w;
        }
        std::sort(w.begin(), w.end());

        std::vector<i64> d(n);
        for (auto &d : d) {
            std::cin >> d;
        }

        if (d[0] != 0 || m < n - 1) {
            std::cout << "NO\n";
            continue;
        }

        std::vector<int> ord(n);
        std::iota(ord.begin(), ord.end(), 0);
        std::sort(ord.begin(), ord.end(), [&](int i, int j) {
            if (d[i] == d[j]) {
                return i < j;
            } else {
                return d[i] < d[j];
            }
        });

        std::vector e(m, std::vector(n, 0));
        for (int i = 1; i < n; i++) {
            int u = ord[i];
            for (int j = 0; j < i; j++) {
                int v = ord[j];
                for (int k = 0; k < m; k++) {
                    if (d[u] - d[v] == w[k]) {
                        e[k][u] = 1;
                    }
                }
            }
        }

        std::vector<int> match(n, -1);
        auto flow = [&]() {
            std::vector<int> vis(n);
            auto dfs = [&](auto &&self, int i) -> bool {
                for (int j = 0; j < n; j++) {
                    if (!vis[j] && e[i][j]) {
                        vis[j] = 1;
                        if (match[j] == -1 || self(self, match[j])) {
                            match[j] = i;
                            return true;
                        }
                    }
                }
                return false;
            };
            int res = 0;
            for (int i = 0; i < m; i++) {
                vis.assign(n, 0);
                res += dfs(dfs, i);
            }
            return res;
        };

        if (flow() != n - 1) {
            std::cout << "NO\n";
            continue;
        }

        std::vector<int> vis(m);
        for (int i = 1; i < n; i++) {
            vis[match[i]] = 1;
        }

        int min = inf;
        for (int i = 0; i < m; i++) {
            if (!vis[i]) {
                min = std::min(min, w[i]);
            }
        }

        bool ok = false;
        for (int i = 0; i < m; i++) {
            if (vis[i]) {
                ok |= w[i] <= min;
            }
        }

        if (ok) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
