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

        std::vector<std::array<int, 3>> ans;
        ans.push_back({0, 0, n});
        for (int i = 1; i < n; i++) {
            ans.push_back({i, 0, i});
            ans.push_back({i, i, n});
        }

        std::cout << ans.size() << "\n";
        for (auto [i, l, r] : ans) {
            std::cout << i + 1 << " " << l + 1 << " " << r << "\n";
        }
    }

    return 0;
}
