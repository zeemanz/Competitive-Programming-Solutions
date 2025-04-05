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

        std::vector<std::vector<int>> adj(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            std::cin >> u >> v;
            u--;
            v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        std::vector<int> ans(n), vis(n);
        for (int u = 0; u < n; u++) {
            for (int v : adj[u]) {
                ans[a[u]] |= a[u] == a[v];
                vis[a[v]]++;
                ans[a[v]] |= vis[a[v]] > 1;
            }
            for (int v : adj[u]) {
                vis[a[v]] = 0;
            }
        }

        for (int i = 0; i < n; i++) {
            std::cout << ans[i];
        }
        std::cout << "\n";
    }

    return 0;
}
