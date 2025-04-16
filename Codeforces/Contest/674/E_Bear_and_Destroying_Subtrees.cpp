#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = double;
using f80 = long double;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(10);

    int q;
    std::cin >> q;

    int n = 1;
    std::vector<int> par(n, -1);
    std::vector<std::array<f64, 64>> dp(n);
    std::fill(dp[0].begin() + 1, dp[0].end(), 1);

    while (q--) {
        int o, v;
        std::cin >> o >> v;
        v--;

        if (o == 1) {
            par.push_back(v);
            dp.emplace_back();
            std::fill(dp[n].begin() + 1, dp[n].end(), 1);
            n++;

            std::vector<int> a;
            for (int i = 0, x = n - 1; i < 64 && x != -1; i++, x = par[x]) {
                a.push_back(x);
            }
            for (int i = a.size() - 1; i > 1; i--) {
                auto x = a[i];
                auto y = a[i - 1];
                dp[x][i] /= (dp[y][i - 1] + 1) / 2;
            }
            for (int i = 0; i + 1 < a.size(); i++) {
                auto x = a[i];
                auto y = a[i + 1];
                dp[y][i + 1] *= (dp[x][i] + 1) / 2;
            }
        } else {
            f64 ans = 0;
            for (int d = 1; d < 64; d++) {
                ans += (dp[v][d] - dp[v][d - 1]) * d;
            }

            std::cout << ans - 1 << "\n";
        }
    }

    return 0;
}
