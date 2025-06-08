#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    std::vector<std::vector<int>> adj(n);
    std::vector<int> x(n - 1), y(n - 1), w(n - 1);
    for (int i = 0; i < n - 1; i++) {
        std::cin >> x[i] >> y[i] >> w[i];
        x[i]--;
        y[i]--;

        adj[x[i]].push_back(i);
        adj[y[i]].push_back(i);
    }

    i64 ans = 0;
    auto dfs = [&](auto &&self, int u, int p) -> void {
        for (auto i : adj[u]) {
            int v = x[i] ^ y[i] ^ u;
            if (v == p) {
                continue;
            }
            self(self, v, u);
            ans += 1LL * w[i] * std::abs(a[v]);
            a[u] += a[v];
            a[v] = 0;
        }
    };

    dfs(dfs, 0, -1);
    std::cout << ans << "\n";

    return 0;
}
