#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> c(m);
    std::vector<std::vector<int>> a(n);
    for (int i = 0; i < m; i++) {
        std::cin >> c[i];
        for (int j = 0; j < c[i]; j++) {
            int x;
            std::cin >> x;
            x--;
            a[x].push_back(i);
        }
    }

    std::vector<int> b(n);
    for (auto &b : b) {
        std::cin >> b;
        b--;
    }

    int ans = 0;
    for (auto b : b) {
        for (auto a : a[b]) {
            c[a]--;
            if (c[a] == 0) {
                ans++;
            }
        }
        std::cout << ans << "\n";
    }

    return 0;
}
