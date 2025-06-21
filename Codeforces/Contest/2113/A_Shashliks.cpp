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
        int k, a, b, x, y;
        std::cin >> k >> a >> b >> x >> y;

        if (a > b) {
            std::swap(a, b);
            std::swap(x, y);
        }

        int ans = 0;
        if (k >= b) {
            int cur = (k - b + y) / y;
            if (k - cur * y >= a) {
                cur += (k - cur * y - a + x) / x;
            }
            ans = std::max(ans, cur);
        }
        if (k >= a) {
            ans = std::max(ans, (k - a + x) / x);
        }

        std::cout << ans << "\n";
    }

    return 0;
}
