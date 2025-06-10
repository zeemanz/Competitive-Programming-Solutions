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

        std::set<int> s;
        for (int i = 1; i < n; i++) {
            s.insert(a[i] - a[i - 1]);
        }

        if (s.size() == 1) {
            int d = *s.begin();
            if (d < 0) {
                a[0] += 1LL * d * n;
            } else {
                a[0] -= d;
            }
            if (a[0] >= 0 && (a[0] % (n + 1)) == 0) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
