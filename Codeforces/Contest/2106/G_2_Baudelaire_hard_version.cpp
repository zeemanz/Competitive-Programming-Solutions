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

        std::vector<std::vector<int>> adj(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            std::cin >> u >> v;
            u--;
            v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        std::vector<int> vis(n), siz(n);
        auto calc = [&](auto &&self, int u, int p) -> void {
            siz[u] = 1;
            for (auto v : adj[u]) {
                if (v == p || vis[v]) {
                    continue;
                }
                self(self, v, u);
                siz[u] += siz[v];
            }
        };
        auto find = [&](auto &&self, int u, int p, int s) -> int {
            for (auto v : adj[u]) {
                if (v == p || vis[v]) {
                    continue;
                }
                if (2 * siz[v] > s) {
                    return self(self, v, u, s);
                }
            }
            return u;
        };
        auto query = [&](std::vector<int> a) {
            std::cout << "? 1 " << a.size() << " ";
            for (auto a : a) {
                std::cout << a + 1 << " ";
            }
            std::cout << std::endl;
            int res;
            std::cin >> res;
            return res;
        };
        auto toggle = [&](int u) { std::cout << "? 2 " << u + 1 << std::endl; };

        auto work = [&](auto &&self, int u) -> int {
            calc(calc, u, -1);
            u = find(find, u, -1, siz[u]);
            calc(calc, u, -1);
            vis[u] = 1;

            std::vector<int> a;
            for (auto v : adj[u]) {
                if (!vis[v]) {
                    a.push_back(v);
                }
            }
            if (a.empty()) {
                return u;
            }

            int x = query(a);
            toggle(u);
            int y = query(a);
            if (std::abs(x - y) == 2 * a.size()) {
                return u;
            }

            int l = 0, r = a.size();
            while (r - l > 1) {
                int m = (l + r) / 2;
                std::vector<int> b(a.begin() + l, a.begin() + m);
                int x = query(b);
                toggle(u);
                int y = query(b);
                if (std::abs(x - y) != 2 * b.size()) {
                    r = m;
                } else {
                    l = m;
                }
            }
            return self(self, a[l]);
        };

        std::vector<int> ans(n);
        auto dfs = [&](auto &&self, int u, int p) -> void {
            ans[u] = query({u});
            for (auto v : adj[u]) {
                if (v == p) {
                    continue;
                }
                self(self, v, u);
                ans[v] -= ans[u];
            }
        };
        dfs(dfs, work(work, 0), -1);

        std::cout << "! ";
        for (int i = 0; i < n; i++) {
            std::cout << ans[i] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
