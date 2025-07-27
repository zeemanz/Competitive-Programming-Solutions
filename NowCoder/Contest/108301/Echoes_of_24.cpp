#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

struct HLD {
    int n, cur;
    std::vector<int> siz, top, dep, par, in, out, seq;
    std::vector<std::vector<int>> adj;
    HLD(int n = 0) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        cur = 0;
        siz.resize(n);
        top.resize(n);
        dep.resize(n);
        par.resize(n);
        in.resize(n);
        out.resize(n);
        seq.resize(n);
        adj.assign(n, {});
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int root = 0) {
        top[root] = root;
        dep[root] = 0;
        par[root] = -1;
        dfs(root);
        hld(root);
    }
    void dfs(int u) {
        if (par[u] != -1) {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), par[u]));
        }
        siz[u] = 1;
        for (auto &v : adj[u]) {
            par[v] = u;
            dep[v] = dep[u] + 1;
            dfs(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    }
    void hld(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            hld(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = par[top[u]];
            } else {
                v = par[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
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
        T res = {};
        for (int i = x; i > 0; i -= i & -i) {
            res += a[i - 1];
        }
        return res;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    int select(const T &k) {
        int res = 0;
        T cur = {};
        for (int i = 1 << std::__lg(n); i > 0; i /= 2) {
            if (res + i <= n && cur + a[res + i - 1] < k) {
                res += i;
                cur += a[res - 1];
            }
        }
        return res;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    HLD t(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;

        t.addEdge(u, v);
    }
    t.work();

    Fenwick<i64> fen(n);
    for (int i = 0; i < n; i++) {
        if (a[i] > 1) {
            fen.add(t.in[i], a[i]);
        }
    }

    auto path = [&](int u, int v) {
        int w = t.lca(u, v);
        std::vector<int> p, q;
        while (u != w) {
            p.push_back(u);
            u = t.par[u];
        }
        while (v != w) {
            q.push_back(v);
            v = t.par[v];
        }
        p.push_back(w);
        p.insert(p.end(), q.rbegin(), q.rend());
        p.erase(p.begin());
        return p;
    };

    auto pathSum = [&](int u, int v) {
        i64 res = 0;
        while (t.top[u] != t.top[v]) {
            if (t.dep[t.top[u]] < t.dep[t.top[v]]) {
                std::swap(u, v);
            }
            res += fen.rangeSum(t.in[t.top[u]], t.in[u] + 1);
            u = t.par[t.top[u]];
        }
        if (t.dep[u] > t.dep[v]) {
            std::swap(u, v);
        }
        res += fen.rangeSum(t.in[u], t.in[v] + 1);
        return res;
    };

    while (q--) {
        int o;
        std::cin >> o;

        if (o == 1) {
            int u, v;
            std::cin >> u >> v;
            u--, v--;

            if (pathSum(u, v) > 24) {
                std::cout << "0\n";
                continue;
            }

            if (t.dist(u, v) + 1 >= 24) {
                std::cout << "1\n";
            } else {
                u32 dp = 0;
                if (a[u] <= 24) {
                    dp |= 1U << a[u];
                }
                auto p = path(u, v);
                for (auto u : p) {
                    u32 ndp = dp << a[u];
                    for (int i = a[u]; i <= 24; i += a[u]) {
                        ndp |= (dp >> (i / a[u]) & 1) << i;
                    }
                    dp = ndp;
                }
                std::cout << (dp >> 24 & 1) << "\n";
            }
        } else {
            int i, x;
            std::cin >> i >> x;
            i--;

            if (a[i] > 1) {
                fen.add(t.in[i], -a[i]);
            }
            a[i] = x;
            if (a[i] > 1) {
                fen.add(t.in[i], a[i]);
            }
        }
    }

    return 0;
}
