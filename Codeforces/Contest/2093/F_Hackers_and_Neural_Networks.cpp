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

        std::vector<std::string> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        std::vector c(m, std::vector<std::string>(n));
        for (int i = 0; i < m; i++) {
            for (auto &c : c[i]) {
                std::cin >> c;
            }
        }

        bool ok = true;
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = 0; j < m; j++) {
                cnt += a[i] == c[j][i];
            }
            ok &= cnt > 0;
        }

        if (!ok) {
            std::cout << "-1\n";
            continue;
        }

        std::vector<int> v(m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                v[i] += a[j] == c[i][j];
            }
        }

        int max = *std::ranges::max_element(v);
        std::cout << n + 2 * (n - max) << "\n";
    }

    return 0;
}
