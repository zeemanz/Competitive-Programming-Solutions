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
