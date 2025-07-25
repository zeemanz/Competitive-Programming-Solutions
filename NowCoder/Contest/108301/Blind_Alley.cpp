#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr std::pair<int, int> d[] = {{-1, 0}, {1, 0}, {0, 1}};

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;
    k++;

    std::vector<std::string> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::vector r(n, std::vector(m, -1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '0') {
                r[i][j] = j + 1;
            }
        }
    }
    for (int k = m - 2; k >= 0; k--) {
        for (int i = 0, j = 0; i < n; i = j) {
            if (a[i][k] == '0') {
                int x = k + 1;
                while (j < n && a[j][k] == '0') {
                    x = std::max(x, r[j][k + 1]);
                    j++;
                }
                while (i < j) {
                    r[i][k] = x;
                    i++;
                }
            } else {
                j++;
            }
        }
    }

    std::vector vis(n, std::vector(m, 0));
    std::queue<std::pair<int, int>> que;
    vis[0][0] = 1;
    que.emplace(0, 0);
    while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop();
        for (auto [dx, dy] : d) {
            int nx = x + dx, ny = y + dy;
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || a[nx][ny] == '1' || vis[nx][ny]) {
                continue;
            }
            vis[nx][ny] = 1;
            que.emplace(nx, ny);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (vis[i][j] && r[i][j] < m - 1 && j - 1 + k <= r[i][j]) {
                std::cout << "Yes\n";
                return;
            }
        }
    }

    std::cout << "No\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
