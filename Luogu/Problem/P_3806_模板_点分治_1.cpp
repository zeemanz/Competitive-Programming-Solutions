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
        for (auto v : adj[u]) {
            if (vis[v]) {
                continue;
            }
            v = find(v);
            par[v] = u;
            dfs(v);
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    CentroidTree t(n);
    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--;
        v--;

        t.addEdge(u, v);
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    std::vector<int> que(m), ans(m);
    for (auto &k : que) {
        std::cin >> k;
    }

    std::vector<int> vis(n), dis(n);
    auto dfs = [&](auto &&self, int u, int p) -> std::vector<int> {
        std::vector<int> res{dis[u]};
        for (auto [v, w] : adj[u]) {
            if (v == p || vis[v]) {
                continue;
            }
            dis[v] = dis[u] + w;
            auto cur = self(self, v, u);
            res.insert(res.end(), cur.begin(), cur.end());
        }
        return res;
    };

    const int K = *std::max_element(que.begin(), que.end());
    std::vector<int> has(K + 1);
    auto work = [&](auto &&self, int u) -> void {
        vis[u] = 1;
        has[0] = 1;
        std::vector<int> tmp{0};
        for (auto [v, w] : adj[u]) {
            if (vis[v]) {
                continue;
            }
            dis[v] = w;
            auto cur = dfs(dfs, v, u);
            for (auto x : cur) {
                for (int i = 0; i < m; i++) {
                    int k = que[i];
                    if (k >= x) {
                        ans[i] |= has[k - x];
                    }
                }
            }
            for (auto x : cur) {
                if (x <= K) {
                    has[x] = 1;
                    tmp.push_back(x);
                }
            }
        }
        for (auto x : tmp) {
            has[x] = 0;
        }
        for (auto v : t.adj[u]) {
            self(self, v);
        }
    };
    work(work, t.work());

    for (int i = 0; i < m; i++) {
        if (ans[i]) {
            std::cout << "AYE\n";
        } else {
            std::cout << "NAY\n";
        }
    }

    return 0;
}
