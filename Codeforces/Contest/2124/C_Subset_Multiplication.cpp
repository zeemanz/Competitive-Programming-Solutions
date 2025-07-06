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

        std::vector<int> b(n);
        for (auto &b : b) {
            std::cin >> b;
        }

        int x = 1;
        for (int i = n - 2; i >= 0; i--) {
            int g = std::gcd(b[i], b[i + 1]);
            x = std::lcm(x, b[i] / g);
            b[i] = g;
        }

        std::cout << x << "\n";
    }

    return 0;
}
