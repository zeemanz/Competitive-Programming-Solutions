#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<i64> h(n), d(n), c(n);
    for (auto &h : h) {
        std::cin >> h;
    }
    for (auto &d : d) {
        std::cin >> d;
    }
    for (auto &c : c) {
        std::cin >> c;
    }

    i64 H = *std::max_element(h.begin(), h.end());
    std::vector sum(n + 1, std::vector(H + 2, 0LL));
    std::vector cnt(n + 1, std::vector(H + 2, 0LL));
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i];
        cnt[i + 1] = cnt[i];
        for (int j = h[i]; j <= H; j++) {
            sum[i + 1][j + 1] += h[i];
            cnt[i + 1][j + 1]++;
        }
    }

    std::vector<i64> dp(H + 1);
    for (int i = n - 1; i >= 0; i--) {
        auto ndp = dp;
        for (int j = 0; j < H; j++) {
            i64 nj = std::min(j + d[i], H);
            ndp[nj] =
                std::max(ndp[nj], dp[j] + (cnt[i + 1][H + 1] - cnt[i + 1][nj]) * (nj - j) +
                                      (sum[i + 1][nj] - sum[i + 1][j]) - (cnt[i + 1][nj] - cnt[i + 1][j]) * j - c[i]);
        }
        dp = std::move(ndp);
    }
    std::cout << *std::ranges::max_element(dp) << "\n";

    return 0;
}
