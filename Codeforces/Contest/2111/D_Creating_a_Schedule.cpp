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

        std::vector<int> f(m);
        for (auto &f : f) {
            std::cin >> f;
        }
        std::sort(f.begin(), f.end());

        int l = 0, r = m - 1;
        while (n >= 2) {
            for (int i = 0; i < 3; i++) {
                std::cout << f[l] << " " << f[r] << " \n"[i == 2];
            }
            for (int i = 0; i < 3; i++) {
                std::cout << f[r] << " " << f[l] << " \n"[i == 2];
            }
            l++;
            r--;
            n -= 2;
        }
        if (n > 0) {
            for (int i = 0; i < 3; i++) {
                std::cout << f[l] << " " << f[r] << " \n"[i == 2];
            }
        }
    }

    return 0;
}
