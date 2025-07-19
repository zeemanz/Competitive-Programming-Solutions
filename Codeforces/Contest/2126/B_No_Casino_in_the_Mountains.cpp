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

        int ans = 0;
        for (int i = 0; i < n;) {
            if (a[i] == 1) {
                i++;
            } else {
                int j = i;
                while (j < n && j - i < k && a[j] == 0) {
                    j++;
                }
                if (j - i == k) {
                    ans++;
                    i = j + 1;
                } else {
                    i = j;
                }
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
