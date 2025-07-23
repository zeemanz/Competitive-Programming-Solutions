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
        int n, a, b;
        std::cin >> n >> a >> b;

        int r = n % (a + b);
        if (0 < r && r <= a) {
            if (r == n) {
                std::cout << "Sayonara\n";
            } else {
                std::cout << r << "\n";
            }
        } else {
            std::cout << 0 << "\n";
        }
    }

    return 0;
}
