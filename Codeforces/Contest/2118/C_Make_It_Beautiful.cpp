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
        u64 k;
        std::cin >> n >> k;

        std::vector<u64> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        int ans = 0;
        for (auto a : a) {
            ans += std::popcount(a);
        }

        for (int i = 0; i < 60; i++) {
            for (auto a : a) {
                if ((~a >> i & 1) && k >= (1ULL << i)) {
                    ans++;
                    k -= 1ULL << i;
                }
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
