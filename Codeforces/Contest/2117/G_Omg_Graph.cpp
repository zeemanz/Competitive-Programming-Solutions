#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr int inf = 1E9;

struct DSU {
    std::vector<int> par, val;
    DSU(int n) {
        init(n);
    }
    void init(int n) {
        par.resize(n);
        std::iota(par.begin(), par.end(), 0);
        val.assign(n, inf);
    }
    int find(int x) {
        if (x == par[x]) {
            return x;
        }
        val[par[x]] = std::min(val[par[x]], val[x]);
        return par[x] = find(par[x]);
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
        par[y] = x;
        val[x] = std::min(val[x], val[y]);
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

        std::vector<std::array<int, 3>> e(m);
        for (auto &[w, u, v] : e) {
            std::cin >> u >> v >> w;
            u--;
            v--;
        }
        std::sort(e.begin(), e.end());

        DSU dsu(n);
        int ans = 2 * inf;
        for (auto [w, u, v] : e) {
            u = dsu.find(u);
            v = dsu.find(v);
            dsu.val[u] = std::min(dsu.val[u], w);
            dsu.val[v] = std::min(dsu.val[v], w);
            dsu.merge(u, v);
            if (dsu.same(0, n - 1)) {
                ans = std::min(ans, w + dsu.val[dsu.find(0)]);
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
