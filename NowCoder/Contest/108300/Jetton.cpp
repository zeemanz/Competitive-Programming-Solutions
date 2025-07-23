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
        int x, y;
        std::cin >> x >> y;

        int ans = 0;
        while (ans < 31 && y != 0) {
            if (x <= y) {
                y -= x;
                x *= 2;
            } else {
                x -= y;
                y *= 2;
            }
            ans++;
        }
        if (y != 0) {
            ans = -1;
        }

        std::cout << ans << "\n";
    }

    return 0;
}
