#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

struct DSU {
    std::vector<int> par, siz;
    DSU(int n = 0) {
        init(n);
    }
    void init(int n) {
        par.resize(n);
        std::iota(par.begin(), par.end(), 0);
        siz.assign(n, 1);
    }
    int find(int x) {
        while (x != par[x]) {
            x = par[x] = par[par[x]];
        }
        return x;
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        par[y] = x;
        siz[x] += siz[y];
        return true;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    DSU dsu(n);
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        dsu.merge(u, v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto dfs = [&](auto &&self, int n, int m, auto &&adj) -> bool {
        if (n == 0 || m == 0) {
            return true;
        }
        DSU dsu(n);
        for (int i = 0; i < n; i++) {
            for (int j : adj[i]) {
                dsu.merge(i, j);
            }
        }
        int cnt = 0;
        std::vector<int> iso(n);
        for (int i = 0; i < n; i++) {
            if (dsu.find(i) == i) {
                if (dsu.siz[i] == 1) {
                    iso[i] = 1;
                } else {
                    cnt++;
                }
            }
        }
        if (cnt == 0) {
            return true;
        }
        if (cnt > 1) {
            return false;
        }
        int s = 0;
        while (iso[s]) {
            s++;
        }
        auto check = [&](auto &&a) {
            int cnt = a.size();
            std::vector<int> vis(n);
            for (auto a : a) {
                vis[a] = 2;
                for (auto b : adj[a]) {
                    if (vis[b] == 0) {
                        vis[b] = 1;
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                if (vis[i] == 0) {
                    for (int j : adj[i]) {
                        if (vis[j] == 0) {
                            return false;
                        }
                        if (vis[j] == 1) {
                            vis[j] = 2;
                            cnt++;
                        }
                    }
                }
            }
            std::vector<int> bad(n);
            for (int i = 0; i < n; i++) {
                if (vis[i] == 1) {
                    int x = 0, y = 0;
                    for (auto j : adj[i]) {
                        x += vis[j] == 1;
                        y += vis[j] == 2;
                    }
                    if (x == 0 || y != cnt) {
                        bad[i] = 1;
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                if (bad[i]) {
                    for (int j : adj[i]) {
                        if (bad[j]) {
                            return false;
                        }
                        if (vis[j] == 1) {
                            cnt++;
                            vis[j] = 2;
                        }
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                if (vis[i] == 2) {
                    int cur = 0;
                    for (int j : adj[i]) {
                        cur += vis[j] == 2;
                    }
                    if (cur != cnt - 1) {
                        return false;
                    }
                }
            }
            std::vector<int> p;
            for (int i = 0; i < n; i++) {
                if (vis[i] == 1 && !bad[i]) {
                    p.push_back(i);
                }
            }
            int nn = p.size(), nm = 0;
            std::vector<std::vector<int>> nadj(nn);
            for (int i = 0; i < nn; i++) {
                for (auto j : adj[p[i]]) {
                    int x = std::ranges::lower_bound(p, j) - p.begin();
                    if (x < nn && p[x] == j) {
                        nm++;
                        nadj[i].push_back(x);
                    }
                }
            }
            return self(self, nn, nm / 2, nadj);
        };
        if (check(std::vector{s})) {
            return true;
        } else {
            return check(adj[s]);
        }
    };

    std::cout << (dfs(dfs, n, m, adj) ? "YES" : "NO") << "\n";

    return 0;
}
