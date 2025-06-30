#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::set<std::vector<int>> ans;
    for (int m = 1; m <= n; m++) {
        std::vector<int> a(m);
        auto dfs = [&](auto &&self, int i, int s) -> void {
            if (i == m) {
                if (s == n) {
                    ans.insert(a);
                }
                return;
            }
            for (int x = 1; s + x <= n; x++) {
                if (i == 0 || x != a[i - 1]) {
                    a[i] = x;
                    self(self, i + 1, s + x);
                }
            }
        };
        dfs(dfs, 0, 0);
    }

    for (auto a : ans) {
        for (int i = 0; i < a.size(); i++) {
            std::cout << a[i] << " \n"[i + 1 == a.size()];
        }
    }

    return 0;
}
