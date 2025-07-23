#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    auto lowbit = [&](u64 x) { return x & -x; };
    auto popcount = [&](u64 x) { return std::popcount(x); };

    while (t--) {
        u64 n, x, y;
        std::cin >> n >> x >> y;

        if (x == y) {
            std::cout << "0\n";
        } else if (popcount(x) == popcount(y) || lowbit(x) == lowbit(y)) {
            std::cout << "1\n";
        } else {
            std::cout << "2\n";
        }
    }

    return 0;
}
