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
        int x, k;
        std::cin >> x >> k;

        auto isPrime = [&](int x) {
            for (int d = 2; d * d <= x; d++) {
                if (x % d == 0) {
                    return false;
                }
            }
            return x > 1;
        };

        if (x == 1) {
            for (int i = 1; i < k; i++) {
                x = 10 * x + 1;
            }
            if (isPrime(x)) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        } else if (k > 1) {
            std::cout << "NO\n";
        } else {
            if (isPrime(x)) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }
    }

    return 0;
}
