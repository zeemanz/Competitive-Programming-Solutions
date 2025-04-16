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
        int n, k;
        std::cin >> n >> k;

        std::vector<int> x(n);
        for (auto &x : x) {
            std::cin >> x;
        }

        std::vector<int> cnt(2 * n + 1);
        for (auto x : x) {
            cnt[x]++;
        }

        int ans = 0;
        for (int x = 1; 2 * x < k; x++) {
            ans += std::min(cnt[x], cnt[k - x]);
        }
        if (k % 2 == 0) {
            ans += cnt[k / 2] / 2;
        }

        std::cout << ans << "\n";
    }

    return 0;
}
