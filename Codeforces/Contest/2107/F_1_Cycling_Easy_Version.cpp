#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<i64> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        std::vector<int> l(n), stk;
        for (int i = 0; i < n; i++) {
            while (!stk.empty() && a[stk.back()] > a[i]) {
                stk.pop_back();
            }
            if (!stk.empty()) {
                l[i] = stk.back() + 1;
            } else {
                l[i] = 0;
            }
            stk.push_back(i);
        }

        std::vector<i64> dp(n + 1, inf);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i; j >= 0; j--) {
                dp[i + 1] = std::min(dp[i + 1], i + a[j] - j + a[j] * (i - l[j]) + (i - l[j]) + dp[l[j]]);
            }
        }
        std::cout << dp[n] << "\n";
    }

    return 0;
}
