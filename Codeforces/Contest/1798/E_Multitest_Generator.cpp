#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr int inf = 1E9;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        int max = 0;
        std::vector<int> f(n + 1), g(n + 1);
        for (int i = n - 1; i >= 0; i--) {
            if (i + a[i] + 1 == n) {
                f[i] = 1;
                g[i] = max + 1;
            } else if (i + a[i] + 1 < n) {
                if (f[i + a[i] + 1] > 0) {
                    f[i] = f[i + a[i] + 1] + 1;
                }
                g[i] = std::max(max, g[i + a[i] + 1]) + 1;
            } else {
                g[i] = max + 1;
            }
            max = std::max(max, f[i]);
        }

        for (int i = 0; i < n - 1; i++) {
            if (a[i] == f[i + 1]) {
                std::cout << "0";
            } else if (f[i + 1] > 0 || g[i + 1] >= a[i]) {
                std::cout << "1";
            } else {
                std::cout << "2";
            }
            std::cout << " \n"[i + 1 == n - 1];
        }
    }

    return 0;
}
