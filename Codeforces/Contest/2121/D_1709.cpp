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
        std::cin >> n;

        std::vector<int> a(n), b(n);
        for (auto &a : a) {
            std::cin >> a;
            a--;
        }
        for (auto &b : b) {
            std::cin >> b;
            b--;
        }

        std::vector<std::pair<int, int>> ans;
        auto work = [&](int k, int i) {
            ans.emplace_back(k, i + 1);
            if (k == 1) {
                std::swap(a[i], a[i + 1]);
            } else if (k == 2) {
                std::swap(b[i], b[i + 1]);
            } else {
                std::swap(a[i], b[i]);
            }
        };

        for (int i = 0; i < n; i++) {
            for (int j = 0; j + 1 < n - i; j++) {
                if (a[j] > a[j + 1]) {
                    work(1, j);
                }
                if (b[j] > b[j + 1]) {
                    work(2, j);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (a[i] > b[i]) {
                work(3, i);
            }
        }

        std::cout << ans.size() << "\n";
        for (auto [k, i] : ans) {
            std::cout << k << " " << i << "\n";
        }
    }

    return 0;
}
