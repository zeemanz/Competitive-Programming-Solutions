#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    u64 k;
    std::cin >> n >> k;

    auto dfs = [&](auto &&self, int n, u64 k) -> void {
        if (n == -1) {
            return;
        }
        if (k < (1ULL << n)) {
            std::cout << "0";
            self(self, n - 1, k);
        } else {
            std::cout << "1";
            self(self, n - 1, (1ULL << n) - (k - (1ULL << n)) - 1);
        }
    };
    dfs(dfs, n - 1, k);

    return 0;
}
