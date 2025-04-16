#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

struct DSU {
    std::vector<int> par, siz;
    DSU() {}
    DSU(int n) {
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
        par[y] = x;
        siz[x] += siz[y];
        return true;
    }
    int size(int x) {
        return siz[find(x)];
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, m1, m2;
        std::cin >> n >> m1 >> m2;

        std::vector<std::pair<int, int>> f, g;
        for (int i = 0; i < m1; i++) {
            int u, v;
            std::cin >> u >> v;
            u--;
            v--;
            f.emplace_back(u, v);
        }
        for (int i = 0; i < m2; i++) {
            int u, v;
            std::cin >> u >> v;
            u--;
            v--;
            g.emplace_back(u, v);
        }

        int ans = 0;
        DSU F(n), G(n);
        for (auto [u, v] : g) {
            G.merge(u, v);
        }
        for (auto [u, v] : f) {
            if (!G.same(u, v)) {
                ans++;
            } else {
                F.merge(u, v);
            }
        }
        for (auto [u, v] : g) {
            ans += F.merge(u, v);
        }

        std::cout << ans << "\n";
    }

    return 0;
}
