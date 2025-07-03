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
        int n, m, k;
        std::cin >> n >> m >> k;

        std::string s;
        std::cin >> s;

        int ans = 0;
        for (int i = 0; i < n;) {
            if (s[i] == '0') {
                int j = i;
                while (j - i < m && j < n && s[j] == '0') {
                    j++;
                }
                if (j - i == m) {
                    ans++;
                    i = j + k - 1;
                } else {
                    i = j;
                }
            } else {
                i++;
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
