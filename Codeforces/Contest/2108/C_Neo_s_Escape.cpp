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

        std::vector<int> a;
        for (int i = 0; i < n; i++) {
            int x;
            std::cin >> x;

            if (!a.empty() && a.back() == x) {
                a.pop_back();
            }
            a.push_back(x);
        }

        int ans = 0;
        for (int i = 0; i < a.size(); i++) {
            int v = 1;
            if (i - 1 >= 0) {
                v &= a[i] > a[i - 1];
            }
            if (i + 1 < a.size()) {
                v &= a[i] > a[i + 1];
            }
            ans += v;
        }
        std::cout << ans << "\n";
    }

    return 0;
}
