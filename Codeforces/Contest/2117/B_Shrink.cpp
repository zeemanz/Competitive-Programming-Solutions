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

        int l = 0, r = n - 1, x = 0;
        std::vector<int> a(n);
        while (l <= r) {
            a[l] = x++;
            l++;
            if (l <= r) {
                a[r] = x++;
                r--;
            }
        }

        for (int i = 0; i < n; i++) {
            std::cout << a[i] + 1 << " \n"[i == n - 1];
        }
    }

    return 0;
}
