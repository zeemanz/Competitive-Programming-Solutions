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
        int n;
        std::cin >> n;

        std::vector<i64> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        if (n > 3) {
            std::cout << n * *std::max_element(a.begin(), a.end()) << "\n";
        } else if (n == 3) {
            i64 ans = a[0] + a[1] + a[2];
            ans = std::max(ans, 3 * a[0]);
            ans = std::max(ans, 3 * a[2]);
            ans = std::max(ans, 3 * std::abs(a[0] - a[1]));
            ans = std::max(ans, 3 * std::abs(a[1] - a[2]));
            ans = std::max(ans, 3 * std::abs(a[0] - a[2]));
            std::cout << ans << "\n";
        } else {
            std::cout << std::max(a[0] + a[1], 2 * std::abs(a[0] - a[1])) << "\n";
        }
    }

    return 0;
}
