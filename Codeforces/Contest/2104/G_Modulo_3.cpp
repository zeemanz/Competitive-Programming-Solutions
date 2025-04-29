#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int power(int a, int b, int m) {
    int res = 1;
    for (; b > 0; b /= 2, a = (a * a) % m) {
        if (b % 2 == 1) {
            res = (res * a) % m;
        }
    }
    return res;
}

struct DSU {
    std::vector<int> par, siz, stk;
    DSU() {}
    DSU(int n) {
        init(n);
    }
    void init(int n) {
        par.resize(n);
        std::iota(par.begin(), par.end(), 0);
        siz.assign(n, 1);
        stk.clear();
    }
    int find(int x) {
        while (x != par[x]) {
            x = par[x];
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
        stk.push_back(y);
        return true;
    }
    int size() {
        return stk.size();
    }
    void undo() {
        int y = stk.back();
        stk.pop_back();
        siz[par[y]] -= siz[y];
        par[y] = y;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> g(n);
    for (int i = 0; i < n; i++) {
        std::cin >> g[i];
        g[i]--;
    }

    std::vector<int> t(n);
    std::vector<std::vector<std::pair<int, int>>> edges(4 << std::__lg(q));
    auto rangeApply = [&](int x, int y, const std::pair<int, int> &e) {
        auto dfs = [&](auto &&self, int p, int l, int r) {
            if (l >= y || r <= x) {
                return;
            }
            if (l >= x && r <= y) {
                edges[p].emplace_back(e);
                return;
            }
            int m = (l + r) / 2;
            self(self, 2 * p, l, m);
            self(self, 2 * p + 1, m, r);
        };
        dfs(dfs, 1, 0, q);
    };

    std::vector<int> k(q);
    for (int i = 0; i < q; i++) {
        int x, y;
        std::cin >> x >> y >> k[i];
        x--;
        y--;
        k[i] %= 3;

        rangeApply(t[x], i, {x, g[x]});
        g[x] = y;
        t[x] = i;
    }
    for (int i = 0; i < n; i++) {
        rangeApply(t[i], q, {i, g[i]});
    }

    DSU dsu(2 * n);
    int tot = n, odd = 0;
    std::vector<int> ans(q);
    auto work = [&](auto &&self, int p, int l, int r) -> void {
        int tmp = dsu.size(), cur = 0;
        for (auto [u, v] : edges[p]) {
            if (dsu.find(u) == dsu.find(v)) {
                cur++;
            } else {
                if (dsu.merge(u, n + v)) {
                    tot--;
                }
                dsu.merge(v, n + u);
            }
        }
        odd += cur;
        if (r - l == 1) {
            ans[l] = power(k[l], n - (tot - odd), 3);
        } else {
            int m = (l + r) / 2;
            self(self, 2 * p, l, m);
            self(self, 2 * p + 1, m, r);
        }
        while (dsu.size() > tmp) {
            dsu.undo();
            dsu.undo();
            tot++;
        }
        odd -= cur;
    };
    work(work, 1, 0, q);

    for (int i = 0; i < q; i++) {
        std::cout << ans[i] << "\n";
    }

    return 0;
}
