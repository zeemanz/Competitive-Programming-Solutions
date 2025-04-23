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

        int ans = s[0] != '0';
        for (int i = 0; i + 1 < n; i++) {
            ans += s[i] != s[i + 1];
        }
        if (ans > 0) {
            ans = std::max(1, ans - 2);
        }

        std::cout << ans + n << "\n";
    }

    return 0;
}
