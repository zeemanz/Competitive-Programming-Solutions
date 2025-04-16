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
        int a[5]{};
        for (int i : {0, 1, 3, 4}) {
            std::cin >> a[i];
        }

        int ans = 1;
        for (int x : {a[0] + a[1], a[3] - a[1], a[4] - a[3]}) {
            a[2] = x;
            int res = 0;
            for (int i = 0; i < 3; i++) {
                res += a[i] + a[i + 1] == a[i + 2];
            }
            ans = std::max(ans, res);
        }

        std::cout << ans << "\n";
    }

    return 0;
}
