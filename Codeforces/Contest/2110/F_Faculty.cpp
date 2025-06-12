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

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        auto f = [&](int x, int y) { return (x % y) + (y % x); };

        int ans = 0, max = 0;
        for (int i = 0; i < n; i++) {
            if (2 * max <= a[i]) {
                for (int j = 0; j < i; j++) {
                    ans = std::max(ans, f(a[i], a[j]));
                }
            } else {
                ans = std::max(ans, f(max, a[i]));
            }
            max = std::max(max, a[i]);

            std::cout << ans << " \n"[i == n - 1];
        }
    }

    return 0;
}
