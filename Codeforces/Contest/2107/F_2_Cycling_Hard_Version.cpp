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
        stk.clear();

        std::vector<i64> dp(n + 1, inf);
        dp[0] = 0;
        auto f = [&](int i) { return a[i] - i - a[i] * l[i] - l[i] + dp[l[i]]; };
        for (int i = 0; i < n; i++) {
            while (!stk.empty() && a[stk.back()] >= a[i]) {
                stk.pop_back();
            }
            auto check = [&](int i, int j, int k) {
                return (f(j) - f(i)) * (a[k] - a[j]) >= (f(k) - f(j)) * (a[j] - a[i]);
            };
            while (stk.size() > 1) {
                int k = stk.end()[-2], j = stk.end()[-1];
                if (check(k, j, i)) {
                    stk.pop_back();
                } else {
                    break;
                }
            }
            stk.push_back(i);
            while (stk.size() > 1) {
                int k = stk.end()[-2], j = stk.end()[-1];
                if (f(k) + i * (a[k] + 2) < f(j) + i * (a[j] + 2)) {
                    stk.pop_back();
                } else {
                    break;
                }
            }
            int j = stk.back();
            dp[i + 1] = std::min(dp[i + 1], f(j) + i * (a[j] + 2));
        }

        for (int i = 1; i <= n; i++) {
            std::cout << dp[i] << " \n"[i == n];
        }
    }

    return 0;
}
