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

        std::vector<i64> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        bool ok = true;
        for (int k = 2; k <= n / 2; k++) {
            std::vector<int> cnt(k);
            for (auto a : a) {
                cnt[a % k]++;
            }
            if (*std::min_element(cnt.begin(), cnt.end()) > 1) {
                ok = false;
            }
        }

        std::sort(a.begin(), a.end());
        a.erase(std::unique(a.begin(), a.end()), a.end());
        ok &= a.size() == n;

        if (ok) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
