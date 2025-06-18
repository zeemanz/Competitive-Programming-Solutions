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

        std::vector a(n, std::vector(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                std::cin >> a[i][j];
            }
        }

        int max = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                max = std::max(max, a[i][j]);
            }
        }

        int cnt = 0;
        std::vector<int> r(n), c(m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cnt += a[i][j] == max;
                r[i] += a[i][j] == max;
                c[j] += a[i][j] == max;
            }
        }

        bool ok = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (r[i] + c[j] - (a[i][j] == max) == cnt) {
                    ok = true;
                }
            }
        }

        std::cout << max - ok << "\n";
    }

    return 0;
}
