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

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<int> p(n), d(n);
        for (auto &p : p) {
            std::cin >> p;
            p--;
        }
        for (auto &d : d) {
            std::cin >> d;
            d--;
        }

        DSU dsu(n);
        for (int i = 0; i < n; i++) {
            dsu.merge(i, p[i]);
        }

        int ans = 0;
        std::vector<int> vis(n);
        for (int i = 0; i < n; i++) {
            int j = dsu.find(d[i]);
            if (!vis[j]) {
                ans += dsu.siz[j];
            }
            vis[j] = 1;
            std::cout << ans << " \n"[i == n - 1];
        }
    }

    return 0;
}
