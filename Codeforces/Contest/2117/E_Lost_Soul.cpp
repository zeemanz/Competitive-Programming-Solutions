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

        std::vector<int> a(n), b(n);
        for (auto &a : a) {
            std::cin >> a;
            a--;
        }
        for (auto &b : b) {
            std::cin >> b;
            b--;
        }

        int ans = -1;
        std::set<int> s[2], t;
        for (int i = n - 1; i >= 0; i--) {
            if (a[i] == b[i]) {
                ans = std::max(ans, i);
            }
            if (i % 2) {
                if (s[0].contains(a[i]) || s[1].contains(b[i])) {
                    ans = std::max(ans, i);
                }
                s[0].insert(b[i]);
                s[1].insert(a[i]);
            } else {
                if (s[1].contains(a[i]) || s[0].contains(b[i])) {
                    ans = std::max(ans, i);
                }
                s[0].insert(a[i]);
                s[1].insert(b[i]);
            }
            if (t.contains(a[i]) || t.contains(b[i])) {
                ans = std::max(ans, i);
            }
            if (i + 1 < n) {
                t.insert(a[i + 1]);
                t.insert(b[i + 1]);
            }
        }

        std::cout << ans + 1 << "\n";
    }

    return 0;
}
