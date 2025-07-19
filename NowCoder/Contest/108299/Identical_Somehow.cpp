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

        if (x != 1 && y != 1) {
            std::cout << "1\n";
        } else {
            std::cout << "-1\n";
        }
    }

    return 0;
}
