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
        int n, s;
        std::cin >> n >> s;

        int l = s, r = s;
        for (int i = 0; i < n; i++) {
            int x;
            std::cin >> x;

            l = std::min(l, x);
            r = std::max(r, x);
        }

        std::cout << std::min(s - l, r - s) + r - l << "\n";
    }

    return 0;
}
