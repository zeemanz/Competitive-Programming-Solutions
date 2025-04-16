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

        std::vector<i64> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        i64 ans = 0;
        if (k == 1) {
            ans = std::max(ans, a[0] + a[n - 1]);
            for (int i = 1; i < n - 1; i++) {
                ans = std::max(ans, std::max(a[0], a[n - 1]) + a[i]);
            }
        } else {
            std::ranges::sort(a, std::greater());
            for (int i = 0; i < k + 1; i++) {
                ans += a[i];
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
