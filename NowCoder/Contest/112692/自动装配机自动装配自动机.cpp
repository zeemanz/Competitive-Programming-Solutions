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
        int n, a, b;
        std::cin >> n >> a >> b;

        i64 A = -b, B = a + 1LL * b * n - 1, C = n;
        auto f = [&](int x) { return A * x * x + B * x + C; };

        i64 ans = 1LL * std::max(a, 1) * n;
        if (A != 0) {
            i64 x = -B / (2 * A);
            for (int i = x - 10; i <= x + 10; i++) {
                if (0 <= i && i <= n) {
                    ans = std::max(ans, f(i));
                }
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
