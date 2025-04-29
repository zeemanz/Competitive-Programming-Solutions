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

        std::vector<i64> sum(n + 1);
        for (int i = 0; i < n; i++) {
            sum[i + 1] = sum[i] + a[i];
        }

        std::vector<int> max(n + 1);
        for (int i = 0; i < n; i++) {
            max[i + 1] = std::max(max[i], a[i]);
        }

        for (int k = 1; k <= n; k++) {
            std::cout << sum[n] - sum[n - k + 1] + max[n - k + 1] << " \n"[k == n];
        }
    }

    return 0;
}
