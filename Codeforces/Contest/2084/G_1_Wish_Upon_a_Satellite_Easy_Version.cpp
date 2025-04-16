#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr i64 inf = 1E18;

template <class T> void chmax(T &a, T b) {
    a = std::max(a, b);
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
        a--;
    }

    std::vector<int> pos(n, -1);
    for (int i = 0; i < n; i++) {
        if (a[i] != -1) {
            pos[a[i]] = (i + 1) % 2;
        }
    }

    int m = (n + 1) / 2;
    std::vector dp(n + 1, std::vector(m + 1, -inf));
    dp[0][0] = 0;

    i64 ans = 1LL * n * (n + 1) * (n + 1) / 4 - (1LL * n * n * n - n) / 12;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y <= m; y++) {
            if (pos[x] == -1) {
                if (y + 1 <= m) {
                    chmax(dp[x + 1][y + 1], dp[x][y] + (2LL * y - m + 1) * (x + 1));
                }
                if (x + 1 - y <= n - m) {
                    chmax(dp[x + 1][y], dp[x][y] + (2LL * (x - y) - n + m + 1) * (x + 1));
                }
            } else if (pos[x] == 0) {
                if (x + 1 - y <= n - m) {
                    chmax(dp[x + 1][y], dp[x][y] + (2LL * (x - y) - n + m + 1) * (x + 1));
                }
            } else {
                if (y + 1 <= m) {
                    chmax(dp[x + 1][y + 1], dp[x][y] + (2LL * y - m + 1) * (x + 1));
                }
            }
        }
    }

    std::cout << ans + dp[n][m] << "\n";
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
