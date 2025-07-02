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

template <class T> struct Fenwick {
    int n;
    std::vector<T> a;
    Fenwick(int n = 0) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        a.assign(n, {});
    }
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    T sum(int x) {
        T res{};
        for (int i = x; i > 0; i -= i & -i) {
            res += a[i - 1];
        }
        return res;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    CentroidTree t(n);
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;

        t.addEdge(u, v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    t.work();

    const int logn = std::__lg(n);
    std::vector<int> dep(n);
    std::vector par(logn + 1, std::vector(n, -1));
    auto dfs = [&](auto &&self, int u) -> void {
        for (int i = 0; (2 << i) <= dep[u]; i++) {
            par[i + 1][u] = par[i][par[i][u]];
        }
        for (auto v : adj[u]) {
            if (v == par[0][u]) {
                continue;
            }
            par[0][v] = u;
            dep[v] = dep[u] + 1;
            self(self, v);
        }
    };
    dfs(dfs, 0);

    auto lca = [&](int x, int y) {
        if (dep[x] < dep[y]) {
            std::swap(x, y);
        }
        for (int i = logn; i >= 0; i--) {
            if (dep[x] - dep[y] >= (1 << i)) {
                x = par[i][x];
            }
        }
        for (int i = logn; i >= 0; i--) {
            if (par[i][x] != par[i][y]) {
                x = par[i][x];
                y = par[i][y];
            }
        }
        if (x != y) {
            x = par[0][x];
        }
        return x;
    };
    auto dis = [&](int x, int y) {
        int z = lca(x, y);
        return dep[x] + dep[y] - 2 * dep[z];
    };

    std::vector<Fenwick<int>> sum(n), del(n);
    for (int i = 0; i < n; i++) {
        sum[i].init(t.siz[i]);
        int p = t.par[i];
        if (p != -1) {
            del[i].init(t.siz[i] + 1);
        }
    }
    auto modify = [&](int x, int y) {
        for (int u = x; u != -1; u = t.par[u]) {
            sum[u].add(dis(u, x), y);
            int p = t.par[u];
            if (p != -1) {
                del[u].add(dis(p, x), y);
            }
        }
    };
    for (int i = 0; i < n; i++) {
        modify(i, a[i]);
    }

    int ans = 0;
    while (m--) {
        int o;
        std::cin >> o;

        if (o == 0) {
            int x, k;
            std::cin >> x >> k;
            x ^= ans;
            k ^= ans;
            x--;

            ans = 0;
            for (int u = x; u != -1; u = t.par[u]) {
                if (dis(u, x) <= k) {
                    ans += sum[u].sum(std::min(k - dis(u, x) + 1, t.siz[u]));
                }
                int p = t.par[u];
                if (p != -1 && dis(p, x) <= k) {
                    ans -= del[u].sum(std::min(k - dis(p, x) + 1, t.siz[u] + 1));
                }
            }

            std::cout << ans << "\n";
        } else {
            int x, y;
            std::cin >> x >> y;
            x ^= ans;
            y ^= ans;
            x--;

            modify(x, y - a[x]);
            a[x] = y;
        }
    }

    return 0;
}
