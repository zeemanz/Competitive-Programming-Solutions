#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr std::pair<int, int> d[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, m;
        std::cin >> n >> m;

        std::vector a(n, std::vector(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                std::cin >> a[i][j];
            }
        }

        std::vector<std::array<int, 3>> que;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }
                bool ok = false;
                for (auto [dx, dy] : d) {
                    int x = i + dx, y = j + dy;
                    if (x < 0 || x >= n || y < 0 || y >= m) {
                        continue;
                    }
                    ok |= a[x][y] > a[i][j];
                }
                if (!ok) {
                    que.push_back({a[i][j], j, i});
                }
            }
        }

        que.push_back({a[0][0], 0, 0});
        std::sort(que.begin(), que.end());

        auto f = [&](int x, int y, int h) {
            i64 res = 1LL << 34;
            res += 114LL * std::abs(x);
            res += 5141LL * std::abs(y);
            res += 919810LL * std::abs(h);
            return res;
        };

        i64 ans = 0;
        for (int i = 0; i + 1 < que.size(); i++) {
            auto [h, y, x] = que[i];
            auto [nh, ny, nx] = que[i + 1];
            ans += f(x - nx, y - ny, h - nh);
        }

        std::cout << ans << "\n";
    }

    return 0;
}
