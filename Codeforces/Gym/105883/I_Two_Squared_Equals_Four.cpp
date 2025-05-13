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

        std::vector<std::pair<i64, i64>> p(n);
        for (auto &[x, y] : p) {
            std::cin >> x >> y;
        }

        std::map<std::pair<i64, i64>, int> s;
        for (int i = 0; i < n; i++) {
            s[p[i]] = i;
        }

        i64 tot = 0;
        std::vector<i64> sum(n);
        for (int i = 0; i < n; i++) {
            auto [xi, yi] = p[i];
            for (int j = 0; j < n; j++) {
                auto [xj, yj] = p[j];
                if (xi < xj && yi <= yj) {
                    if (s.contains({xj - yj + yi, yj + xj - xi})) {
                        if (s.contains({xi - yj + yi, yi + xj - xi})) {
                            int k = s[{xj - yj + yi, yj + xj - xi}];
                            int l = s[{xi - yj + yi, yi + xj - xi}];
                            tot++;
                            sum[i]++;
                            sum[j]++;
                            sum[k]++;
                            sum[l]++;
                        }
                    }
                }
            }
        }

        i64 ans = 0;
        for (int i = 0; i < n; i++) {
            ans = std::max(ans, tot - sum[i]);
        }
        std::cout << ans << "\n";
    }

    return 0;
}
