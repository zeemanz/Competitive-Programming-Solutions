#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::string s;
    std::cin >> s;

    std::vector<int> pos(k, n);
    std::vector next(n, std::vector(k, n));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < k; j++) {
            next[i][j] = pos[j];
        }
        pos[s[i] - 'a'] = i;
    }

    std::vector<int> dp(n + 1, n);
    dp[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < k; j++) {
            dp[i] = std::min(dp[i], dp[next[i][j]] + 1);
        }
    }

    int q;
    std::cin >> q;

    while (q--) {
        std::string t;
        std::cin >> t;

        int i = -1;
        for (auto c : t) {
            if (i == -1) {
                i = pos[c - 'a'];
            } else {
                i = next[i][c - 'a'];
            }
            if (i == n) {
                break;
            }
        }

        std::cout << dp[i] << "\n";
    }

    return 0;
}
