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

        if (n == 2) {
            std::cout << "-1\n";
            continue;
        }

        if (n % 2 == 0) {
            std::cout << n / 2 << " ";
            for (int i = 1; i < n / 2; i++) {
                std::cout << i << " ";
            }
            for (int i = n; i > n / 2; i--) {
                std::cout << i << " ";
            }
            std::cout << "\n";
        } else {
            for (int i = 0; i < (n - 1) / 2; i++) {
                std::cout << n - i << " ";
            }
            for (int i = (n - 1) / 2; i < n; i++) {
                std::cout << i - (n - 1) / 2 + 1 << " ";
            }
            std::cout << "\n";
        }
    }

    return 0;
}
