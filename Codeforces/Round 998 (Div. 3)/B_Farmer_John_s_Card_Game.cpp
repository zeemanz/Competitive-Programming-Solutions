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

        std::vector a(n, std::vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (auto &a : a[i]) {
                std::cin >> a;
            }
            std::ranges::sort(a[i]);
        }

        std::vector<int> ord(n);
        std::iota(ord.begin(), ord.end(), 0);
        std::ranges::sort(ord, [&](int i, int j) {
            return a[i][0] < a[j][0];
        });

        int p = -1;
        bool ok = true;
        for (int j = 0; j < m; j++) {
            for (int i : ord) {
                if (a[i][j] <= p) {
                    ok = false;
                    break;
                }
                p = a[i][j];
            }
        }

        if (ok) {
            for (int i = 0; i < n; i++) {
                std::cout << ord[i] + 1 << " \n"[i == n - 1];
            }
        } else {
            std::cout << "-1\n";
        }
    }

    return 0;
}
