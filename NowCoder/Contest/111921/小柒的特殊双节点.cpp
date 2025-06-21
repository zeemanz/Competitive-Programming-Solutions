#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

struct HLD {
    int n;
    std::vector<int> siz, top, dep, par, in, out, seq;
    std::vector<std::vector<int>> adj;
    int cur;
    HLD() {}
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        siz.resize(n);
        top.resize(n);
        dep.resize(n);
        par.resize(n);
        in.resize(n);
        out.resize(n);
        seq.resize(n);
        cur = 0;
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
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if (par[u] != -1) {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), par[u]));
        }
        siz[u] = 1;
        for (auto &v : adj[u]) {
            par[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    }
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
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
    int jump(int u, int k) {
        if (dep[u] < k) {
            return -1;
        }
        int d = dep[u] - k;
        while (dep[top[u]] > d) {
            u = par[top[u]];
        }
        return seq[in[u] - dep[u] + d];
    }
    bool isAncester(int u, int v) {
        return in[u] <= in[v] && in[v] < out[u];
    }
    int rootedParent(int u, int v) {
        std::swap(u, v);
        if (u == v) {
            return u;
        }
        if (!isAncester(u, v)) {
            return par[u];
        }
        auto it = std::upper_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y) { return in[x] < in[y]; }) - 1;
        return *it;
    }
    int rootedSize(int u, int v) {
        if (u == v) {
            return n;
        }
        if (!isAncester(v, u)) {
            return siz[v];
        }
        return n - siz[rootedParent(u, v)];
    }
    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};

struct Trie {
    struct Node {
        int cnt;
        std::array<int, 2> next;
        Node() : cnt{}, next{} {}
    };
    std::vector<Node> t;
    Trie() {
        init();
    }
    void init() {
        t.assign(1, {});
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    void insert(int p, int q, u32 x) {
        for (int i = 29; i >= 0; i--) {
            u32 b = x >> i & 1;
            if (!t[p].next[b]) {
                t[p].next[b] = newNode();
            }
            t[p].next[b ^ 1] = t[q].next[b ^ 1];
            p = t[p].next[b];
            q = t[q].next[b];
            t[p].cnt = t[q].cnt + 1;
        }
    }
    u32 query(int p, std::vector<std::pair<int, int>> seg, u32 x) {
        u32 res = 0;
        for (int i = 29; i >= 0; i--) {
            u32 b = x >> i & 1;
            int c = t[t[p].next[b ^ 1]].cnt;
            for (auto [l, r] : seg) {
                c -= t[t[r].next[b ^ 1]].cnt - t[t[l].next[b ^ 1]].cnt;
            }
            if (c > 0) {
                res |= 1U << i;
                b ^= 1;
            }
            p = t[p].next[b];
            for (auto &[l, r] : seg) {
                l = t[l].next[b];
                r = t[r].next[b];
            }
        }
        return res;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<u32> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    HLD t(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        t.addEdge(u, v);
    }
    t.work();

    Trie trie;
    std::vector<int> root(n + 1);
    for (int i = 0; i < n; i++) {
        root[i + 1] = trie.newNode();
        trie.insert(root[i + 1], root[i], a[t.seq[i]]);
    }

    for (int i = 0; i < n; i++) {
        std::vector<std::pair<int, int>> seg;
        seg.emplace_back(root[t.in[i]], root[t.out[i]]);
        for (int u = t.par[i]; u != -1; u = t.par[t.top[u]]) {
            seg.emplace_back(root[t.in[t.top[u]]], root[t.in[u] + 1]);
        }
        std::cout << trie.query(root[n], seg, a[i]) << " \n"[i + 1 == n];
    }

    return 0;
}
