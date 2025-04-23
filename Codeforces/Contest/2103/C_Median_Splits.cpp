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
            a = a <= k ? 1 : -1;
        }

        std::vector<int> sum(n + 1);
        for (int i = 0; i < n; i++) {
            sum[i + 1] = sum[i] + a[i];
        }

        std::multiset<int> s;
        for (int i = 1; i < n; i++) {
            s.insert(sum[i]);
        }

        bool ok = false;
        for (int i = 1; i <= n - 2; i++) {
            s.extract(sum[i]);
            if (sum[i] >= 0) {
                if (sum[i] <= *s.rbegin() || *s.begin() <= sum[n]) {
                    ok = true;
                }
            } else {
                auto it = s.lower_bound(sum[i]);
                if (it != s.end() && *it <= sum[n]) {
                    ok = true;
                }
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
