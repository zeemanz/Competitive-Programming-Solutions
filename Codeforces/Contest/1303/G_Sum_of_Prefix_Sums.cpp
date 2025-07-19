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

template <class T, T inf, class C = std::less<>> struct LiChaoSegmentTree {
    static constexpr C cmp = {};
    struct Line {
        T k, b;
        constexpr Line(T k = 0, T b = std::max(-inf, inf, cmp)) : k{k}, b{b} {}
        constexpr T operator()(T x) const {
            return k * x + b;
        }
    };
    struct Node {
        Node *l, *r;
        Line f;
        Node() : l{}, r{}, f{} {}
    };
    int n;
    Node *t;
    LiChaoSegmentTree(int n = 0) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        t = nullptr;
    }
    void insert(Node *&p, int l, int r, int x, int y, Line f) {
        if (l >= y || r <= x) {
            return;
        }
        if (p == nullptr) {
            p = new Node();
        }
        int m = (l + r) / 2;
        if (l >= x && r <= y) {
            if (cmp(f(m), p->f(m))) {
                std::swap(f, p->f);
            }
            if (r - l == 1) {
                return;
            }
            if (cmp(f(l), p->f(l))) {
                insert(p->l, l, m, x, y, f);
            } else {
                insert(p->r, m, r, x, y, f);
            }
        } else {
            insert(p->l, l, m, x, y, f);
            insert(p->r, m, r, x, y, f);
        }
    }
    void insert(int l, int r, Line f) {
        insert(t, 0, n, l, r, f);
    }
    void insert(Line f) {
        insert(t, 0, n, 0, n, f);
    }
    T query(Node *p, int l, int r, int x) {
        if (p == nullptr) {
            return Line()(x);
        }
        if (r - l == 1) {
            return p->f(x);
        }
        int m = (l + r) / 2;
        if (x < m) {
            return std::min(p->f(x), query(p->l, l, m, x), cmp);
        } else {
            return std::min(p->f(x), query(p->r, m, r, x), cmp);
        }
    }
    T query(int x) {
        return query(t, 0, n, x);
    }
};

constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

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

    std::vector<int> vis(n);
    LiChaoSegmentTree<i64, inf, std::greater<>> seg;
    auto query = [&](auto &&self, int u, int p, int len, i64 cur, i64 sum) -> i64 {
        len++;
        sum += a[u];
        cur += sum;
        i64 res = seg.query(len) + cur;
        for (auto v : adj[u]) {
            if (vis[v] || v == p) {
                continue;
            }
            res = std::max(res, self(self, v, u, len, cur, sum));
        }
        return res;
    };
    auto insert = [&](auto &&self, int u, int p, int len, i64 cur, i64 sum) -> void {
        len++;
        cur += 1LL * len * a[u];
        sum += a[u];
        seg.insert({sum, cur});
        for (auto v : adj[u]) {
            if (vis[v] || v == p) {
                continue;
            }
            self(self, v, u, len, cur, sum);
        }
    };

    i64 ans = 0;
    auto work = [&](int u) {
        seg.init(t.siz[u] + 1);
        seg.insert({0, 0});
        for (auto v : adj[u]) {
            if (vis[v]) {
                continue;
            }
            ans = std::max(ans, query(query, v, u, 1, a[u], a[u]));
            insert(insert, v, u, 0, 0, 0);
        }
        ans = std::max(ans, seg.query(1) + a[u]);
    };
    auto dfs = [&](auto &&self, int u) -> void {
        vis[u] = 1;
        work(u);
        std::reverse(adj[u].begin(), adj[u].end());
        work(u);
        for (auto v : t.adj[u]) {
            self(self, v);
        }
    };
    dfs(dfs, t.work());

    std::cout << ans << "\n";

    return 0;
}
