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
        int n, m;
        std::cin >> n >> m;

        std::vector<int> f(n + 1);
        f[0] = f[1] = 1;
        for (int i = 2; i <= n; i++) {
            f[i] = f[i - 1] + f[i - 2];
        }

        std::vector<std::array<int, 3>> box(m);
        for (auto &[w, l, h] : box) {
            std::cin >> w >> l >> h;
        }

        for (auto [w, l, h] : box) {
            if (std::min({w, l, h}) >= f[n] && std::max({w, l, h}) >= f[n] + f[n - 1]) {
                std::cout << "1";
            } else {
                std::cout << "0";
            }
        }
        std::cout << "\n";
    }

    return 0;
}
