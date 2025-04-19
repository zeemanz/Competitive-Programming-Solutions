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
        int n, k;
        std::cin >> n >> k;

        std::vector<int> l(n), r(n);
        for (int i = 0; i < n; i++) {
            std::cin >> l[i];
        }
        for (int i = 0; i < n; i++) {
            std::cin >> r[i];
        }

        std::vector<int> min(n);
        for (int i = 0; i < n; i++) {
            min[i] = std::min(l[i], r[i]);
        }
        std::sort(min.begin(), min.end(), std::greater());

        i64 ans = 1;
        for (int i = 0; i < n; i++) {
            ans += std::max(l[i], r[i]);
        }
        for (int i = 0; i < k - 1; i++) {
            ans += min[i];
        }
        std::cout << ans << "\n";
    }

    return 0;
}
