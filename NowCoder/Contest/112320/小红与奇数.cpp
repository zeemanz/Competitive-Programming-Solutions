#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int x;
    std::cin >> x;

    if (x % 2 == 1) {
        std::cout << "No\n";
    } else {
        std::cout << "Yes\n";
    }

    return 0;
}
