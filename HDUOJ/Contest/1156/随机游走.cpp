#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int cur = 0;
    std::vector<i64> val;
    std::vector<int> dfn(n, -1), low(n), bel(n, -1), siz, stk;
    auto tarjan = [&](auto &&self, int u, int p) -> void {
        dfn[u] = low[u] = cur++;
        stk.push_back(u);
        for (auto v : g[u]) {
            if (v == p) {
                continue;
            }
            if (dfn[v] == -1) {
                self(self, v, u);
                low[u] = std::min(low[u], low[v]);
            } else if (bel[v] == -1) {
                low[u] = std::min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            int v;
            val.emplace_back();
            siz.emplace_back();
            do {
                v = stk.back();
                stk.pop_back();
                bel[v] = val.size() - 1;
                val.back() += a[v];
                siz.back()++;
            } while (v != u);
            m++;
        }
    };
    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) {
            tarjan(tarjan, i, -1);
        }
    }

    std::vector<std::vector<int>> h(val.size());
    for (int u = 0; u < n; u++) {
        for (auto v : g[u]) {
            if (bel[u] != bel[v]) {
                h[bel[u]].push_back(bel[v]);
            }
        }
    }

    i64 ans = 0, sum = 0, res[2]{};
    std::vector<int> ok(n);
    std::vector<std::array<i64, 2>> max(n);
    auto dfs = [&](auto &&self, int u, int p) -> void {
        ok[u] = siz[u] > 1;
        for (auto v : h[u]) {
            if (v == p) {
                continue;
            }
            self(self, v, u);
            ok[u] |= ok[v];
            if (!ok[v]) {
                i64 cur = max[v][0];
                for (int i = 0; i < 2; i++) {
                    if (cur > max[u][i]) {
                        std::swap(cur, max[u][i]);
                    }
                }
            }
        }
        if (ok[u]) {
            sum += val[u];
            for (i64 cur : max[u]) {
                for (int i = 0; i < 2; i++) {
                    if (cur > res[i]) {
                        std::swap(cur, res[i]);
                    }
                }
            }
        } else {
            i64 cur = max[u][1];
            for (int i = 0; i < 2; i++) {
                if (cur > res[i]) {
                    std::swap(cur, res[i]);
                }
            }
        }
        max[u][0] += val[u];
        ans = std::max(ans, max[u][0] + max[u][1]);
    };

    int r = 0;
    for (int i = 0; i < siz.size(); i++) {
        if (siz[i] > 1) {
            r = i;
        }
    }
    dfs(dfs, r, -1);

    std::cout << std::max(ans, sum + res[0] + res[1]) << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
