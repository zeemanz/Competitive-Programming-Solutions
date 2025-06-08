#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr int inf = 2000000001;

struct DSU {
    std::vector<int> par, siz;
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

    int n, q;
    std::cin >> n >> q;

    std::vector<std::pair<int, int>> p(n);
    for (auto &[x, y] : p) {
        std::cin >> x >> y;
    }

    auto d = [&](int i, int j) {
        auto [xi, yi] = p[i];
        auto [xj, yj] = p[j];
        return std::abs(xi - xj) + std::abs(yi - yj);
    };

    std::priority_queue<std::array<int, 3>, std::vector<std::array<int, 3>>, std::greater<>> que;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            que.push({d(i, j), i, j});
        }
    }

    DSU dsu(n + q);
    while (q--) {
        int o;
        std::cin >> o;

        if (o == 1) {
            int a, b;
            std::cin >> a >> b;
            p.emplace_back(a, b);

            for (int i = 0; i < n; i++) {
                que.push({d(i, n), i, n});
            }
            n++;
        } else if (o == 2) {
            int res = inf;
            while (!que.empty()) {
                auto [d, u, v] = que.top();
                if (res == inf || d == res) {
                    if (dsu.merge(u, v)) {
                        res = d;
                    }
                    que.pop();
                } else {
                    break;
                }
            }
            if (res == inf) {
                res = -1;
            }
            std::cout << res << "\n";
        } else {
            int u, v;
            std::cin >> u >> v;
            u--;
            v--;

            if (dsu.same(u, v)) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        }
    }

    return 0;
}
