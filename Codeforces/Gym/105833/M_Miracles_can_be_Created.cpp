#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    u32 n;
    std::cin >> n;

    if (n % 2 == 0) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}
