#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<int> a(n), b(n);
        for (auto &a : a) {
            std::cin >> a;
            a--;
        }
        for (auto &b : b) {
            std::cin >> b;
            b--;
        }

        std::vector<int> vis(2 * n);
        std::vector<std::vector<int>> adj(2 * n);
        for (int i = 0; i < n; i++) {
            if (a[i] == b[i]) {
                continue;
            }
            vis[a[i]] = 1;
            vis[b[i]] = 1;
            adj[a[i]].push_back(i);
            adj[b[i]].push_back(i);
        }

        int cur = 0;
        std::vector<int> dfn(2 * n, -1), low(2 * n), stk, bel(2 * n, -1);
        std::vector<std::vector<int>> bcc;
        auto dfs = [&](auto &&self, int u, int e) -> void {
            dfn[u] = low[u] = cur++;
            stk.push_back(u);
            for (auto i : adj[u]) {
                if (i == e) {
                    continue;
                }
                int v = u ^ a[i] ^ b[i];
                if (dfn[v] == -1) {
                    self(self, v, i);
                    low[u] = std::min(low[u], low[v]);
                } else if (bel[v] == -1) {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }
            if (dfn[u] == low[u]) {
                bcc.emplace_back();
                int v;
                do {
                    v = stk.back();
                    stk.pop_back();
                    bel[v] = bcc.size() - 1;
                    bcc.back().push_back(v);
                } while (v != u);
                cur++;
            }
        };
        for (int i = 0; i < 2 * n; i++) {
            if (dfn[i] == -1 && vis[i]) {
                dfs(dfs, i, -1);
            }
        }

        std::vector<std::vector<std::pair<int, int>>> g(bcc.size());
        for (int u = 0; u < 2 * n; u++) {
            for (auto i : adj[u]) {
                int v = u ^ a[i] ^ b[i];
                if (bel[u] != bel[v]) {
                    g[bel[u]].emplace_back(i, bel[v]);
                }
            }
        }

        std::vector<int> use(n);
        auto work = [&](auto &&self, int u, int p) -> void {
            for (auto [i, v] : g[u]) {
                if (v == p || use[i]) {
                    continue;
                }
                use[i] = 1;
                self(self, v, u);
                if (bel[a[i]] != u) {
                    std::swap(a[i], b[i]);
                }
            }
        };
        for (int i = 0; i < bcc.size(); i++) {
            work(work, i, -1);
        }

        vis.assign(2 * n, 0);
        auto work2 = [&](auto &&self, int u) -> void {
            vis[u] = 1;
            for (auto i : adj[u]) {
                if (use[i]) {
                    continue;
                }
                use[i] = 1;
                int v = a[i] ^ b[i] ^ u;
                if (!vis[v]) {
                    self(self, v);
                }
                if (a[i] != u) {
                    std::swap(a[i], b[i]);
                }
            }
        };
        for (auto bcc : bcc) {
            if (bcc.size() == 1) {
                continue;
            }
            for (auto u : bcc) {
                work2(work2, u);
            }
        }

        std::set<int> sa(a.begin(), a.end()), sb(b.begin(), b.end());
        std::cout << sa.size() + sb.size() << "\n";

        for (int i = 0; i < n; i++) {
            std::cout << a[i] + 1 << " \n"[i + 1 == n];
        }
        for (int i = 0; i < n; i++) {
            std::cout << b[i] + 1 << " \n"[i + 1 == n];
        }
    }

    return 0;
}
