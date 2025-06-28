#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::set<std::pair<int, int>> e;
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;

        if (u > v) {
            std::swap(u, v);
        }
        e.emplace(u, v);
    }

    std::vector<int> dp(1 << n, m + n);
    for (int mask = 1; mask < (1 << n); mask++) {
        std::vector<int> p;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                p.push_back(i);
            }
        }
        if (p.size() < 3) {
            continue;
        }
        do {
            int cur = 0;
            for (int i = 0; i < p.size(); i++) {
                int u = p[i], v = p[(i + 1) % p.size()];
                if (u > v) {
                    std::swap(u, v);
                }
                cur += !e.contains({u, v});
            }
            dp[mask] = std::min(dp[mask], cur);
        } while (std::next_permutation(p.begin(), p.end()));
    }

    for (int i = 1; i < (1 << n); i++) {
        for (int j = 1; j <= i; j++) {
            if ((i | j) == i && (i & j) == j) {
                dp[i] = std::min(dp[i], dp[i - j] + dp[j]);
            }
        }
    }

    std::cout << dp[(1 << n) - 1] + m - (n - dp[(1 << n) - 1]) << "\n";

    return 0;
}
