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
        a.push_back(0);

        i64 ans = 1LL * n * n;
        for (int l = 0, r = 1; r <= n; r++) {
            if (a[l] != a[r]) {
                ans = std::min(ans, 1LL * (l + n - r) * a[l]);
                l = r;
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
