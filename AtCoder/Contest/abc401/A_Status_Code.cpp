#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int S;
    std::cin >> S;

    if (200 <= S && S < 300) {
        std::cout << "Success\n";
    } else {
        std::cout << "Failure\n";
    }

    return 0;
}
