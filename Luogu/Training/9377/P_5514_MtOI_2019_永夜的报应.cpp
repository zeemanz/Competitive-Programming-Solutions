#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<u32> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    std::cout << std::accumulate(a.begin(), a.end(), 0U, std::bit_xor<>()) << "\n";

    return 0;
}
