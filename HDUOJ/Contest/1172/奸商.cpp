#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr int N = 3000, M = N / 64 + 1;
u64 dp[17][M], all[M], cur[M];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::string s;
        std::cin >> s;

        std::vector<int> w(17);
        for (auto &w : w) {
            std::cin >> w;
        }

        int len;
        std::cin >> len;

        if (len % 2) {
            len++;
        }

        std::vector<u32> que;
        for (int i = 0; i + len <= n; i++) {
            bool ok = false;
            for (int j = 0; j < len / 2; j++) {
                if (s[i + j] == s[i + len - j - 1]) {
                    ok = true;
                    break;
                }
            }
            if (!ok) {
                u32 mask = 0;
                for (int j = 0; j < len / 2; j++) {
                    if (s[i + j] < s[i + len - j - 1]) {
                        mask |= 1U << (s[i + j] - 'a');
                    } else {
                        mask |= 1U << (s[i + len - j - 1] - 'a');
                    }
                }
                que.push_back(mask);
            }
        }

        if (que.empty()) {
            std::cout << 0 << "\n";
            continue;
        }

        int m = que.size() / 64 + 1;
        for (int i = 0; i < 17; i++) {
            std::fill(dp[i], dp[i] + m, 0ULL);
            for (int j = 0; j < que.size(); j++) {
                int x = j / 64, y = j % 64;
                if (que[j] >> i & 1) {
                    dp[i][x] |= 1ULL << y;
                }
            }
        }

        std::fill(all, all + m, 0ULL);
        for (int i = 0; i < que.size(); i++) {
            int x = i / 64, y = i % 64;
            all[x] |= 1ULL << y;
        }

        int ans = std::accumulate(w.begin(), w.end(), 0);
        for (u32 mask = 0; mask < (1 << 17); mask++) {
            int sum = 0;
            for (int i = 0; i < 17; i++) {
                if (mask >> i & 1) {
                    sum += w[i];
                    for (int j = 0; j < m; j++) {
                        cur[j] |= dp[i][j];
                    }
                }
            }
            bool ok = true;
            for (int i = 0; i < m; i++) {
                ok &= cur[i] == all[i];
                cur[i] = 0;
            }
            if (ok) {
                ans = std::min(ans, sum);
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
