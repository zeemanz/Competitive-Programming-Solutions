#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr int inf = 1E9;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, m;
        std::cin >> n >> m;

        std::vector<std::pair<int, int>> segs(n);
        for (auto &[l, r] : segs) {
            std::cin >> l >> r;
            l--;
        }

        int min = inf, max = 0, minr = inf, maxl = 0;
        for (auto [l, r] : segs) {
            min = std::min(min, r - l);
            max = std::max(max, r - l);
            minr = std::min(minr, r);
            maxl = std::max(maxl, l);
        }

        int ans = max - min;
        for (auto [l, r] : segs) {
            ans = std::max(ans, r - std::max(minr, l));
            ans = std::max(ans, std::min(maxl, r) - l);
        }

        std::cout << 2 * ans << "\n";
    }

    return 0;
}
