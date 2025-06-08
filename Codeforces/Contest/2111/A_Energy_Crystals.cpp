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

        int log = std::__lg(x);
        std::cout << 2 * (log + 1) + 1 << "\n";
    }

    return 0;
}
