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
        int n, x;
        std::cin >> n >> x;

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        int i = std::find(a.begin(), a.end(), 1) - a.begin();
        int j = n;
        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                j = i;
            }
        }

        if (j - i + 1 <= x) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
