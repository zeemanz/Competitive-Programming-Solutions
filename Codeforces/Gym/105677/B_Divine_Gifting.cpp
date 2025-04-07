#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::vector<int> d(n);
    for (auto &d : d) {
        std::cin >> d;
    }

    auto v = d;
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
    k = std::min(k, int(v.size()));

    std::vector<int> ord(n);
    std::iota(ord.begin(), ord.end(), 0);
    std::sort(ord.begin(), ord.end(), [&](int i, int j) { return d[i] < d[j]; });

    std::vector<i64> sum(n + 1), pow(n + 1);
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + d[ord[i]];
        pow[i + 1] = pow[i] + 1LL * d[ord[i]] * d[ord[i]];
    }

    std::vector dp(k + 1, std::vector(n + 1, inf));
    dp[0][0] = 0;
    std::vector prev(k + 1, std::vector(n + 1, 0));
    for (int r = 1; r <= n; r++) {
        for (int l = 0; l < r; l++) {
            for (int i = 0; i <= l && i < k; i++) {
                i64 cur = i64(r - l) * d[ord[r - 1]] * d[ord[r - 1]];
                cur -= 2 * d[ord[r - 1]] * (sum[r] - sum[l]);
                cur += pow[r] - pow[l];
                if (dp[i][l] + cur < dp[i + 1][r]) {
                    dp[i + 1][r] = dp[i][l] + cur;
                    prev[i + 1][r] = l;
                }
            }
        }
    }

    std::vector<int> o(n);
    for (int r = n, i = k; r > 0; r = prev[i][r], i--) {
        o[prev[i][r]] = d[ord[r - 1]];
    }

    std::vector<int> ans(n);
    for (int i = 0, x = 0; i < n; i++) {
        x = std::max(x, o[i]);
        ans[ord[i]] = x;
    }

    for (int i = 0; i < n; i++) {
        std::cout << ans[i] << " \n"[i == n - 1];
    }

    return 0;
}
