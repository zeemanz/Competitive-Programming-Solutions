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
        int n, x;
        std::cin >> n >> x;

        if (x == 0) {
            if (n % 2 == 0) {
                std::cout << n << "\n";
            } else {
                if (n >= 3) {
                    std::cout << n + 3 << "\n";
                } else {
                    std::cout << "-1\n";
                }
            }
            continue;
        }

        int c = std::min(std::popcount(u32(x)), n);
        if ((n - c) % 2 == 0) {
            std::cout << n - c + x << "\n";
        } else {
            if (c > 1) {
                std::cout << n - c + 1 + x << "\n";
            } else {
                if (x == 1) {
                    std::cout << n - c - 2 + 6 << "\n";
                } else {
                    std::cout << n - c + x + 1 << "\n";
                }
            }
        }
    }

    return 0;
}
