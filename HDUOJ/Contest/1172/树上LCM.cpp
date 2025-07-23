#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

struct CentroidTree {
    int n;
    std::vector<int> vis, par, siz;
    std::vector<std::vector<int>> adj;
    CentroidTree(int n = 0) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        vis.assign(n, 0);
        par.assign(n, -1);
        siz.assign(n, 0);
        adj.assign(n, {});
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int work(int root = 0) {
        root = find(root);
        dfs(root);
        adj.assign(n, {});
        for (int i = 0; i < n; i++) {
            if (par[i] != -1) {
                adj[par[i]].push_back(i);
            }
        }
        return root;
    }
    int find(int x) {
        auto dfs = [&](auto &&self, int u, int p = -1) -> void {
            siz[u] = 1;
            for (auto v : adj[u]) {
                if (v == p || vis[v]) {
                    continue;
                }
                self(self, v, u);
                siz[u] += siz[v];
            }
        };
        dfs(dfs, x);
        auto get = [&](auto &&self, int u, int p = -1) -> int {
            for (auto v : adj[u]) {
                if (v == p || vis[v]) {
                    continue;
                }
                if (2 * siz[v] > siz[x]) {
                    return self(self, v, u);
                }
            }
            return u;
        };
        return get(get, x);
    }
    void dfs(int u) {
        vis[u] = 1;
        siz[u] = 1;
        for (auto v : adj[u]) {
            if (vis[v]) {
                continue;
            }
            v = find(v);
            par[v] = u;
            dfs(v);
            siz[u] += siz[v];
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, x;
        std::cin >> n >> x;

        CentroidTree t(n);
        std::vector<std::vector<int>> adj(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            std::cin >> u >> v;
            u--, v--;

            t.addEdge(u, v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        i64 ans = 0;
        std::vector<int> vis(n);
        std::map<int, int> cnt;
        auto query = [&](auto &&self, int u, int p, i64 m) -> void {
            m = std::lcm(m, a[u]);
            if (m > x) {
                return;
            }
            for (auto [k, v] : cnt) {
                if (std::lcm(m, k) == x) {
                    ans += v;
                }
            }
            for (auto v : adj[u]) {
                if (v == p || vis[v]) {
                    continue;
                }
                self(self, v, u, m);
            }
        };
        auto insert = [&](auto &&self, int u, int p, i64 m) -> void {
            m = std::lcm(m, a[u]);
            if (m > x) {
                return;
            }
            cnt[m]++;
            for (auto v : adj[u]) {
                if (v == p || vis[v]) {
                    continue;
                }
                self(self, v, u, m);
            }
        };

        auto dfs = [&](auto &&self, int u) -> void {
            vis[u] = 1;
            cnt[a[u]] = 1;
            ans += a[u] == x;
            for (auto v : adj[u]) {
                if (vis[v]) {
                    continue;
                }
                query(query, v, u, 1);
                insert(insert, v, u, a[u]);
            }
            cnt.clear();
            for (auto v : t.adj[u]) {
                self(self, v);
            }
        };
        dfs(dfs, t.work());

        std::cout << ans << "\n";
    }

    return 0;
}
