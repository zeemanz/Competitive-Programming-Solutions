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
        int n, m;
        std::cin >> n >> m;

        std::vector<int> a(m);
        for (auto &a : a) {
            std::cin >> a;
        }
        std::ranges::sort(a);

        std::vector<i64> f(n);
        for (int x = 1; x < n; x++) {
            f[x] = f[x - 1];
            int y = n - x;
            auto it = std::ranges::lower_bound(a, y);
            f[x] += m - (it - a.begin());
        }

        i64 ans = 0;
        for (auto a : a) {
            ans += f[std::min(a, n - 1)];
            ans -= std::max(std::min(a, n - 1) - std::max(n - a, 1) + 1, 0);
        }

        std::cout << ans << "\n";
    }

    return 0;
}
