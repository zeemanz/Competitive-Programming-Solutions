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

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        for (int i = 0; i + 1 < n; i++) {
            int x = std::min(a[i], a[i + 1]);
            a[i] -=  x;
            a[i + 1] -= x;
        }

        bool ok = true;
        for (int i = 0; i + 1 < n; i++) {
            if (a[i] > a[i + 1]) {
                ok = false;
                break;
            }
        }

        if (ok) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
