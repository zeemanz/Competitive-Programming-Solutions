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
        int n, t;
        std::cin >> n >> t;

        std::string s;
        std::cin >> s;
        s += s;

        std::vector<int> a;
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                int j = i + 1;
                while (s[j] == '0') {
                    j++;
                }
                a.push_back(j - i - 1);
            }
        }

        int sum = 0;
        for (auto a : a) {
            sum += std::max(a - 2 * t, 0);
        }

        int ans = sum;
        for (auto a : a) {
            ans = std::max(ans, sum - std::max(a - 2 * t, 0) + std::max(a - t - 1, 0));
        }

        std::cout << ans << "\n";
    }

    return 0;
}
