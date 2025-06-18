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

        std::string s;
        std::cin >> s;

        std::vector<int> sum(n + 1);
        for (int i = 0; i < n; i++) {
            sum[i + 1] = sum[i] + (s[i] == '0' ? -1 : 1);
        }
        std::sort(sum.begin(), sum.end());

        i64 ans = 0;
        for (int i = 0; i <= n; i++) {
            ans += 1LL * i * sum[i];
            ans -= 1LL * (n - i) * sum[i];
        }
        for (int i = 0; i <= n; i++) {
            ans += 1LL * i * (n - i + 1);
        }

        std::cout << ans / 2 << "\n";
    }

    return 0;
}
