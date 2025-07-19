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

        std::vector<int> p(n), s(n);
        for (auto &p : p) {
            std::cin >> p;
        }
        for (auto &s : s) {
            std::cin >> s;
        }

        std::vector<i64> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = std::lcm<i64>(p[i], s[i]);
        }

        bool ok = true;
        for (i64 i = 0, x = 0; i < n; i++) {
            x = std::gcd(x, a[i]);
            ok &= x == p[i];
        }
        for (i64 i = n - 1, x = 0; i >= 0; i--) {
            x = std::gcd(x, a[i]);
            ok &= x == s[i];
        }

        if (ok) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
