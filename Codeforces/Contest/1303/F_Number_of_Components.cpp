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

constexpr std::array<std::pair<int, int>, 4> d{{{0, -1}, {1, 0}, {0, 1}, {-1, 0}}};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, q;
    std::cin >> n >> m >> q;

    auto id = [&](int x, int y) { return x * m + y; };

    int C = 1;
    std::vector a(n, std::vector(m, 0));
    std::vector<std::vector<std::pair<int, int>>> add(C), del(C);
    for (int i = 0; i < q; i++) {
        int x, y, c;
        std::cin >> x >> y >> c;
        x--;
        y--;

        C = std::max(C, c + 1);
        add.resize(C);
        del.resize(C);

        if (a[x][y] != c) {
            add[c].emplace_back(i, id(x, y));
            del[a[x][y]].emplace_back(i, id(x, y));
            a[x][y] = c;
        }
    }
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            del[a[x][y]].emplace_back(q, id(x, y));
        }
    }
    for (int i = 0; i < C; i++) {
        std::reverse(del[i].begin(), del[i].end());
    }

    std::vector<int> dif(q + 1);
    auto work = [&](int sgn, const std::vector<std::pair<int, int>> &que) {
        DSU dsu(n * m);
        std::vector vis(n, std::vector(m, 0));
        for (auto [i, u] : que) {
            int x = u / m, y = u % m, res = 1;
            for (auto [dx, dy] : d) {
                int nx = x + dx, ny = y + dy;
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                    continue;
                }
                if (vis[nx][ny]) {
                    res -= dsu.merge(id(x, y), id(nx, ny));
                }
            }
            vis[x][y] = 1;
            dif[i] += sgn * res;
        }
    };
    for (int i = 0; i < C; i++) {
        work(+1, add[i]);
        work(-1, del[i]);
    }

    int ans = 1;
    for (int i = 0; i < q; i++) {
        ans += dif[i];
        std::cout << ans << "\n";
    }

    return 0;
}
