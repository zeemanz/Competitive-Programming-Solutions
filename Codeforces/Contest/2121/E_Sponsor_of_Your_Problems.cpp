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
        int l, r;
        std::cin >> l >> r;

        auto f = [&](int x) {
            std::vector<int> a;
            while (x > 0) {
                a.push_back(x % 10);
                x /= 10;
            }
            std::reverse(a.begin(), a.end());
            return a;
        };

        auto a = f(l);
        auto b = f(r);

        std::vector dp(2, std::vector(2, std::vector(a.size(), -1)));
        auto dfs = [&](auto &&self, int i, bool flo, bool fhi) -> int {
            if (i == a.size()) {
                return 0;
            }
            if (dp[flo][fhi][i] != -1) {
                return dp[flo][fhi][i];
            }
            int res = 18, lo = flo ? a[i] : 0, hi = fhi ? b[i] : 9;
            for (int x = lo; x <= hi; x++) {
                int cur = self(self, i + 1, flo & (x == lo), fhi & (x == hi)) + (x == a[i]) + (x == b[i]);
                res = std::min(res, cur);
            }
            return dp[flo][fhi][i] = res;
        };

        std::cout << dfs(dfs, 0, 1, 1) << "\n";
    }

    return 0;
}
