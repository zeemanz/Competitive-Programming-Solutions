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
        int x;
        std::cin >> x;

        int y = 9;
        while (x > 0) {
            int d = x % 10;
            x /= 10;
            y = std::min(y, d);
        }

        std::cout << y << "\n";
    }

    return 0;
}
