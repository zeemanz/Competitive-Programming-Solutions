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
        int n, k;
        std::cin >> n >> k;

        if (n % 2 == 0) {
            if (k % 2 == 1) {
                k--;
            }
            std::cout << (n + k - 1) / k << "\n";
        } else {
            if (k % 2 == 0) {
                n -= k - 1;
            } else {
                n -= k;
                k--;
            }
            std::cout << (n + k - 1) / k + 1 << "\n";
        }
    }

    return 0;
}
