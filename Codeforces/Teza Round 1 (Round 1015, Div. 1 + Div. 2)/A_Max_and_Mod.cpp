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

        if (n % 2 == 0) {
            std::cout << "-1\n";
        } else {
            std::cout << n << " ";
            for (int i = 1; i < n; i++) {
                std::cout << i << " \n"[i == n - 1];
            }
        }
    }

    return 0;
}
