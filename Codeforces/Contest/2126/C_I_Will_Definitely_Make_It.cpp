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
        int n, k;
        std::cin >> n >> k;
        k--;

        std::vector<int> h(n);
        for (auto &h : h) {
            std::cin >> h;
        }

        int x = h[k];
        std::sort(h.begin(), h.end());

        int t = 0;
        for (int i = 0; i < n; i++) {
            if (h[i] <= x) {
                continue;
            }
            if (h[i] - x <= x - t) {
                t += h[i] - x;
                x = h[i];
            } else {
                break;
            }
        }

        if (x == h[n - 1]) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
