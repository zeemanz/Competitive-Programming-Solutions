#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::cout << "44\n";
    for (int i = 1; i <= 41; i += 2) {
        std::cout << "B" << i << " = B" << i - 1 << " << " << std::min(1 << ((i - 1) / 2), n) << "\n";
        std::cout << "B" << i + 1 << " = B" << i - 1 << " | B" << i << "\n";
    }
    std::cout << "B43 = B42 << 1\n";
    std::cout << "B44 = B42 ^ B43\n";

    return 0;
}
