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

        int ans = 1;
        i64 sum = a[0];
        for (int i = 1; i < n; i++) {
            if (a[i] >= sum) {
                ans++;
                sum += a[i];
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
