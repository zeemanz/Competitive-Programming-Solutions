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

        std::sort(a.begin(), a.end());

        int ans = 0;
        i64 sum = 0;
        for (int i = 0; i < n; i++) {
            sum += a[i];

            int lo = 0, hi = i;
            while (lo < hi) {
                int m = (lo + hi) / 2;
                if (1LL * (i + 1) * a[m] > sum) {
                    hi = m;
                } else {
                    lo = m + 1;
                }
            }
            if (1LL * (i + 1) * a[lo] > sum) {
                ans = std::max(ans, i - lo + 1);
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
