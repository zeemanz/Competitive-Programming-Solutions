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
        int n, m;
        std::cin >> n >> m;

        std::string s;
        std::cin >> s;

        i64 ans = 1;
        int l = 0, r = 0;
        int x = n - 1 - std::count(s.begin(), s.end(), 'D');
        int y = m - 1 - std::count(s.begin(), s.end(), 'R');
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'D') {
            } else if (s[i] == 'R') {
                l++;
                r++;
            } else {
                if (y > 0) {
                    r++;
                    y--;
                }
                if (x == 0) {
                    l++;
                } else {
                    x--;
                }
            }
            l = std::max(l, i - n + 2);
            l = std::min(l, m - 1);
            r = std::max(r, i - n + 2);
            r = std::min(r, m - 1);
            ans += r - l + 1;
        }

        std::cout << ans << "\n";
    }

    return 0;
}
