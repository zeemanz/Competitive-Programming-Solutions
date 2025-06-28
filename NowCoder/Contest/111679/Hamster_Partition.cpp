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
        int n, x, d;
        std::cin >> n >> x >> d;

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        std::vector<int> c(n);
        for (auto &c : c) {
            std::cin >> c;
        }

        std::vector<int> w(n);
        for (auto &w : w) {
            std::cin >> w;
        }

        std::vector<int> ord(n);
        std::iota(ord.begin(), ord.end(), 0);
        std::sort(ord.begin(), ord.end(),
                  [&](int i, int j) { return (a[i] + c[i] - 1) / c[i] < (a[j] + c[j] - 1) / c[j]; });

        i64 ans = 0;
        int sum = std::accumulate(a.begin(), a.end(), 0);
        std::vector<i64> dp(sum + 1);
        for (int i : ord) {
            for (int j = sum; j >= a[i]; j--) {
                i64 cur = dp[j - a[i]] + w[i];
                int cnt = std::max((a[i] + c[i] - 1) / c[i], (j + x - 1) / x);
                ans = std::max(ans, cur - 1LL * cnt * d);
            }
            for (int j = sum; j >= a[i]; j--) {
                dp[j] = std::max(dp[j], dp[j - a[i]] + w[i]);
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
