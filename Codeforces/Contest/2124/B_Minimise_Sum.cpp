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

        std::vector<i64> f(n);
        f[0] = a[0];
        for (int i = 1; i < n; i++) {
            f[i] = std::min(f[i - 1], a[i]);
        }

        i64 sum = 0;
        i64 ans = std::accumulate(f.begin(), f.end(), 0LL);
        for (int i = 0; i + 1 < n; i++) {
            if (a[i] != f[i]) {
                ans = std::min(ans, sum + f[i]);
            } else if (i > 0) {
                ans = std::min(ans, sum + std::min(f[i - 1], a[i] + a[i + 1]));
            }
            sum += f[i];
        }
        ans = std::min(ans, a[0] + a[1]);

        std::cout << ans << "\n";
    }

    return 0;
}
