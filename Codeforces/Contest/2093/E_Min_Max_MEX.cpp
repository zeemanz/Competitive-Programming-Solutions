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

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        auto check = [&](int x) {
            int cnt = 0;
            std::vector<int> vis(x);
            for (int l = 0, r = 0, m = 0; r < n; r++) {
                if (a[r] < x) {
                    vis[a[r]] = 1;
                }
                while (m < x && vis[m]) {
                    m++;
                }
                if (m == x) {
                    m = 0;
                    while (l <= r) {
                        if (a[l] < x) {
                            vis[a[l]] = 0;
                        }
                        l++;
                    }
                    cnt++;
                }
            }
            return cnt >= k;
        };

        int lo = 0, hi = n;
        while (lo < hi) {
            int x = (lo + hi + 1) / 2;
            if (check(x)) {
                lo = x;
            } else {
                hi = x - 1;
            }
        }

        std::cout << lo << "\n";
    }

    return 0;
}
