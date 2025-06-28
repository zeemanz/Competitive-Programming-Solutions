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

        std::vector<int> s(n);
        for (auto &s : s) {
            std::cin >> s;
        }
        std::sort(s.begin() + 1, s.end() - 1);

        int ans = 1;
        for (int i = 0, j = 0; i < n - 1; i = j) {
            if (s[n - 1] <= 2 * s[i]) {
                ans++;
                break;
            }
            while (j + 1 < n && s[j + 1] <= 2 * s[i]) {
                j++;
            }
            if (i == j) {
                ans = -1;
                break;
            }
            ans++;
        }

        std::cout << ans << "\n";
    }

    return 0;
}
