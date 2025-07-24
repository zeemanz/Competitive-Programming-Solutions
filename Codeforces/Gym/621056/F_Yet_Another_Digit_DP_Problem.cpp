#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;

constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto isTobo = [&](i128 x) {
        std::vector<int> a;
        while (x > 0) {
            a.push_back(x % 10);
            x /= 10;
        }
        std::reverse(a.begin(), a.end());
        return std::is_sorted(a.begin(), a.end());
    };

    std::vector<i64> a;
    auto dfs = [&](auto &&self, i64 x) -> void {
        if (x > inf) {
            return;
        }
        if (isTobo(i128(x) * x)) {
            a.push_back(x);
        }
        int r = x % 10;
        for (int d = r; d < 10; d++) {
            self(self, 10 * x + d);
        }
    };
    for (int i = 1; i < 10; i++) {
        dfs(dfs, i);
    }
    std::sort(a.begin(), a.end());

    int t;
    std::cin >> t;

    while (t--) {
        i64 m;
        std::cin >> m;

        std::cout << std::upper_bound(a.begin(), a.end(), m) - a.begin() << "\n";
    }

    return 0;
}
