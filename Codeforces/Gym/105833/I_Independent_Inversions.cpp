#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::vector<int> b(n);
    for (auto &b : b) {
        std::cin >> b;
    }

    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        int x = i;
        std::vector<int> a;
        while (a.size() < k) {
            a.push_back(x % 3);
            x /= 3;
        }
        std::reverse(a.begin(), a.end());
        auto dfs = [&](auto &&self, int cur, int j) -> void {
            if (cur == k) {
                ans += b[i] > b[j];
                return;
            }
            for (int d = 0; d < 3; d++) {
                if ((cur == 0 && d < a[cur]) || d == a[cur]) {
                    continue;
                }
                self(self, cur + 1, 3 * j + d);
            }
        };
        dfs(dfs, 0, 0);
    }
    std::cout << ans << "\n";

    return 0;
}
