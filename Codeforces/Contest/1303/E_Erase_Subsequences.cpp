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
        std::string s, t;
        std::cin >> s >> t;
        int n = s.size(), m = t.size();

        bool ok = false;
        for (int i = 0; i < m; i++) {
            std::vector<int> dp(i + 1, -1);
            dp[0] = 0;
            for (int j = 0; j < n; j++) {
                for (int x = i; x >= 0; x--) {
                    if (dp[x] != -1) {
                        if (x < i && s[j] == t[x]) {
                            dp[x + 1] = std::max(dp[x + 1], dp[x]);
                        }
                        if (dp[x] < m - i && s[j] == t[i + dp[x]]) {
                            dp[x]++;
                        }
                    }
                }
            }
            ok |= dp[i] == m - i;
        }

        if (ok) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
