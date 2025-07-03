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
        int a, b;
        std::cin >> a >> b;

        std::cout << std::lcm(a, b) << "\n";
    }

    return 0;
}
