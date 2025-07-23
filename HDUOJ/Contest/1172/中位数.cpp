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
            a--;
        }

        std::vector<int> p(n);
        for (int i = 0; i < n; i++) {
            p[a[i]] = i;
        }

        std::vector<int> f(n + 1);
        for (int i = 0; i < n; i++) {
            f[i + 1] = f[i] - 1;
        }

        i64 ans = 0;
        for (int m = n - 1; m >= 0; m--) {
            for (int i = p[m] + 1; i <= n; i++) {
                f[i] += 2;
            }
            i64 cur = 0;
            std::vector<int> s(2 * n + 1);
            for (int i = 0; i <= p[m]; i++) {
                s[n + f[i]] += i + 1;
            }
            for (int i = p[m] + 1; i <= n; i++) {
                cur += s[n + f[i] - 1] * i;
            }
            ans += cur * (m + 1);
        }

        std::cout << ans << "\n";
    }

    return 0;
}
