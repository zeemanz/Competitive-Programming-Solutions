#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> par(n, -1);
    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        std::cin >> par[i];
        par[i]--;
        adj[par[i]].push_back(i);
    }

    std::vector<int> siz(n), cent(n);
    auto dfs = [&](auto &&self, int x) -> void {
        siz[x] = 1;
        for (auto y : adj[x]) {
            self(self, y);
            siz[x] += siz[y];
        }
        int s = -1;
        for (auto y : adj[x]) {
            if (2 * siz[y] > siz[x]) {
                s = y;
            }
        }
        if (s == -1) {
            cent[x] = x;
        } else {
            int y = cent[s];
            while (2 * (siz[x] - siz[y]) > siz[x]) {
                y = par[y];
            }
            cent[x] = y;
        }
    };
    dfs(dfs, 0);

    while (q--) {
        int x;
        std::cin >> x;
        x--;

        std::cout << cent[x] + 1 << "\n";
    }

    return 0;
}
