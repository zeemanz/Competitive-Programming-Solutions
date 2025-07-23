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
};

template <class Info> struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree(int n = 0, const Info &v = {}) {
        init(n, v);
    }
    void init(int n, const Info &v = {}) {
        init(std::vector(n, v));
    }
    void init(const std::vector<Info> &a) {
        n = a.size();
        if (n == 0) {
            return;
        }
        info.assign(4 << std::__lg(n), {});
        auto dfs = [&](auto &&self, int p, int l, int r) -> void {
            if (r - l == 1) {
                info[p] = a[l];
                return;
            }
            int m = (l + r) / 2;
            self(self, 2 * p, l, m);
            self(self, 2 * p + 1, m, r);
            pull(p);
        };
        dfs(dfs, 1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int x, const Info &v) {
        modify(1, 0, n, x, v);
    }
    Info query(int p, int l, int r, int x) {
        if (r - l == 1) {
            return info[p];
        }
        int m = (l + r) / 2;
        if (x < m) {
            return query(2 * p, l, m, x);
        } else {
            return query(2 * p + 1, m, r, x);
        }
    }
    Info query(int x) {
        return query(1, 0, n, x);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return {};
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        Info lhs = rangeQuery(2 * p, l, m, x, y);
        Info rhs = rangeQuery(2 * p + 1, m, r, x, y);
        return lhs + rhs;
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    template <class F> int findFirst(int p, int l, int r, int x, int y, const F &pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template <class F> int findFirst(int l, int r, const F &pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template <class F> int findLast(int p, int l, int r, int x, int y, const F &pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template <class F> int findLast(int l, int r, const F &pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};

struct Info {
    int x;
    Info(int x = 0) : x{x} {}
};

Info operator+(const Info &lhs, const Info &rhs) {
    Info res;
    res.x = std::max(lhs.x, rhs.x);
    return res;
}

void solve() {
    int n, m;
    std::cin >> n >> m;

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

    SegmentTree<Info> val(n);
    for (int i = 0; i < n; i++) {
        val.modify(t.in[i], {a[i]});
    }

    std::vector<int> add(n);
    while (m--) {
        int o;
        std::cin >> o;

        if (o == 1) {
            int x, y, z;
            std::cin >> x >> y;
            x--, y--, z = t.lca(x, y);

            int ans = 0;
            while (t.top[x] != t.top[y]) {
                if (t.dep[t.top[x]] < t.dep[t.top[y]]) {
                    std::swap(x, y);
                }
                int u = t.top[x];
                ans = std::max(ans, val.rangeQuery(t.in[u], t.in[x] + 1).x);
                if (t.par[u] != -1) {
                    ans = std::max(ans, val.query(t.in[u]).x + add[t.par[u]]);
                }
                x = t.par[u];
            }

            if (t.dep[x] < t.dep[y]) {
                std::swap(x, y);
            }
            ans = std::max(ans, val.rangeQuery(t.in[z], t.in[x] + 1).x);
            if (t.par[z] != -1 && t.top[z] == z) {
                ans = std::max(ans, val.query(t.in[z]).x + add[t.par[z]]);
            }

            std::cout << ans << "\n";
        } else {
            int x, z;
            std::cin >> x >> z;
            x--;

            if (t.par[x] != -1) {
                int u = t.par[x];
                val.modify(t.in[u], {val.query(t.in[u]).x + z});
            }
            if (!t.adj[x].empty()) {
                int u = t.adj[x][0];
                val.modify(t.in[u], {val.query(t.in[u]).x + z});
            }
            add[x] += z;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
