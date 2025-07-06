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
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        if (siz[x] < siz[y]) {
            std::swap(x, y);
        }
        par[y] = x;
        siz[x] += siz[y];
        return true;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
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

        std::vector<int> c(n, -1);
        auto dfs = [&](auto &&self, int u) -> bool {
            for (auto v : adj[u]) {
                if (c[v] == -1) {
                    c[v] = c[u] ^ 1;
                    if (!self(self, v)) {
                        return false;
                    }
                } else if (c[v] == c[u]) {
                    return false;
                }
            }
            return true;
        };

        bool ok = true;
        for (int i = 0; i < n; i++) {
            if (c[i] == -1) {
                c[i] = 0;
                ok &= dfs(dfs, i);
            }
        }

        std::vector<int> siz, cur(n);
        std::vector<std::array<int, 2>> cnt(n);
        for (int i = 0; i < n; i++) {
            if (dsu.find(i) == i) {
                siz.push_back(dsu.siz[i]);
            }
            cur[dsu.find(i)] += adj[i].size();
            cnt[dsu.find(i)][c[i]]++;
        }

        i64 ans = 0;
        if (siz.size() == 1) {
            for (int i = 0; i < n; i++) {
                if (dsu.find(i) == i) {
                    ans += 1LL * cnt[i][0] * cnt[i][1] - cur[i] / 2;
                }
            }
        } else if (siz.size() == 2) {
            int sum = 0;
            for (auto x : siz) {
                ans += 1LL * sum * x;
                sum += x;
            }
        }

        std::cout << ans * ok << "\n";
    }

    return 0;
}
