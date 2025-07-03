#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr std::array<std::pair<int, int>, 4> d{{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, m;
        std::cin >> n >> m;

        std::vector<std::string> g(n + 2);
        g[0].assign(m + 2, 0);
        g[n + 1].assign(m + 2, 0);
        for (int i = 1; i <= n; i++) {
            std::cin >> g[i];
            g[i] = " " + g[i] + " ";
        }

        std::vector f(n + 2, std::vector(m + 2, 0));
        std::queue<std::pair<int, int>> que;
        for (int i : {0, n + 1}) {
            for (int j = 0; j <= m + 1; j++) {
                f[i][j] = 1;
                que.emplace(i, j);
            }
        }
        for (int j : {0, m + 1}) {
            for (int i = 1; i <= n; i++) {
                f[i][j] = 1;
                que.emplace(i, j);
            }
        }
        while (!que.empty()) {
            auto [x, y] = que.front();
            que.pop();
            for (auto [a, b] : d) {
                int nx = x + a, ny = y + b;
                if (nx < 0 || nx > n + 1 || ny < 0 || ny > m + 1 || f[nx][ny]) {
                    continue;
                }
                if (g[nx][ny] == 'U' && a == 1) {
                    f[nx][ny] = 1;
                    que.emplace(nx, ny);
                }
                if (g[nx][ny] == 'D' && a == -1) {
                    f[nx][ny] = 1;
                    que.emplace(nx, ny);
                }
                if (g[nx][ny] == 'L' && b == 1) {
                    f[nx][ny] = 1;
                    que.emplace(nx, ny);
                }
                if (g[nx][ny] == 'R' && b == -1) {
                    f[nx][ny] = 1;
                    que.emplace(nx, ny);
                }
            }
        }

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (g[i][j] == '?') {
                    bool ok = false;
                    for (auto [a, b] : d) {
                        int x = i + a, y = j + b;
                        ok |= !f[x][y];
                    }
                    ans += ok;
                } else {
                    ans += !f[i][j];
                }
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
