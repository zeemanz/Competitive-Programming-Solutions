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

        int hi = 0;
        for (int i = 1; i <= n; i++) {
            hi += std::abs(n - i + 1 - i);
        }
        std::cout << hi / 2 + 1 << "\n";
    }

    return 0;
}
