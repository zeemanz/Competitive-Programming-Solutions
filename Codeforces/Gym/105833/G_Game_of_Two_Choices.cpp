#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr int inf = 1E9;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
    }

    int cur = 0;
    std::vector<int> dfn(n, -1), low(n), stk, bel(n, -1);
    std::vector<std::vector<int>> scc;
    auto dfs = [&](auto &&self, int u, int p) -> void {
        dfn[u] = low[u] = cur++;
        stk.push_back(u);
        for (auto v : adj[u]) {
            if (dfn[v] == -1) {
                self(self, v, u);
                low[u] = std::min(low[u], low[v]);
            } else if (bel[v] == -1) {
                low[u] = std::min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            scc.emplace_back();
            int v;
            do {
                v = stk.back();
                stk.pop_back();
                bel[v] = scc.size() - 1;
                scc.back().push_back(v);
            } while (v != u);
        }
    };
    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) {
            dfs(dfs, i, -1);
        }
    }

    std::vector<int> t(n), d(n);
    for (auto scc : scc) {
        if (scc.size() > 1) {
            for (auto i : scc) {
                t[i] = 2;
                for (auto j : adj[i]) {
                    d[i] += bel[i] == bel[j];
                }
                assert(d[i] > 0);
                if (d[i] == 1) {
                    if (adj[i].size() > 1) {
                        t[i] = 1;
                    }
                }
            }
        } else {
            for (auto i : scc) {
                if (!adj[i].empty()) {
                    t[i] = 1;
                }
            }
        }
    }

    std::vector<int> deg(scc.size());
    std::vector<std::vector<int>> g(scc.size());
    for (int i = 0; i < n; i++) {
        for (auto j : adj[i]) {
            if (bel[i] != bel[j]) {
                g[bel[j]].push_back(bel[i]);
                deg[bel[i]]++;
            }
        }
    }

    std::vector<int> f(n, inf);
    std::queue<int> que;
    for (int i = 0; i < scc.size(); i++) {
        if (deg[i] == 0) {
            que.push(i);
            if (scc[i].size() == 1) {
                f[scc[i][0]] = 0;
            }
        }
    }

    std::vector<int> c(n), max(n, -1), smx(n, -1);
    std::vector<std::vector<int>> bg(n);
    while (!que.empty()) {
        int i = que.front();
        que.pop();
        if (scc[i].size() > 1) {
            for (auto u : scc[i]) {
                for (auto v : adj[u]) {
                    if (bel[u] == bel[v]) {
                        bg[v].push_back(u);
                    }
                }
            }
            std::queue<int> sque;
            for (auto u : scc[i]) {
                if (t[u] == 1) {
                    sque.push(u);
                    c[u] = d[u];
                }
            }
            while (!sque.empty()) {
                int u = sque.front();
                sque.pop();
                for (auto v : bg[u]) {
                    c[v]++;
                    if (t[v] == 2 && c[v] >= d[v] - 1) {
                        t[v] = 3;
                        sque.push(v);
                    }
                }
            }
            std::priority_queue<std::pair<int, int>> heap;
            for (auto u : scc[i]) {
                if (t[u] != 2) {
                    int &a = max[u], &b = smx[u];
                    a = inf;
                    for (auto v : adj[u]) {
                        if (bel[u] != bel[v]) {
                            if (f[v] + 1 > a) {
                                b = a;
                                a = f[v] + 1;
                            } else if (f[v] + 1 > b) {
                                b = f[v] + 1;
                            }
                        }
                    }
                    if (b == -1) {
                        f[u] = a;
                    } else {
                        f[u] = b;
                    }
                    heap.emplace(-f[u], u);
                }
            }
            while (!heap.empty()) {
                auto [du, u] = heap.top();
                heap.pop();
                if (-du != f[u]) {
                    continue;
                }
                for (auto v : bg[u]) {
                    if (t[v] != 2) {
                        if (f[u] + 1 > max[v]) {
                            smx[v] = max[v];
                            max[v] = f[u] + 1;
                        } else if (f[u] + 1 > smx[v]) {
                            smx[v] = f[u] + 1;
                        }
                        if (smx[v] == -1) {
                            if (max[v] < f[v]) {
                                f[v] = max[v];
                                heap.emplace(-f[v], v);
                            }
                        } else if (smx[v] < f[v]) {
                            f[v] = smx[v];
                            heap.emplace(-f[v], v);
                        }
                    }
                }
            }
            for (auto u : scc[i]) {
                max[u] = smx[u] = -1;
            }
            for (auto u : scc[i]) {
                if (t[u] != 2) {
                    int &a = max[u], &b = smx[u];
                    for (auto v : adj[u]) {
                        if (bel[u] == bel[v]) {
                            if (f[v] + 1 > a) {
                                a = f[v] + 1;
                            }
                        }
                    }
                    for (auto v : adj[u]) {
                        if (bel[u] != bel[v]) {
                            if (f[v] + 1 > a) {
                                b = a;
                                a = f[v] + 1;
                            } else if (f[v] + 1 > b) {
                                b = f[v] + 1;
                            }
                        }
                    }
                    if (b == -1) {
                        f[u] = a;
                    } else {
                        f[u] = b;
                    }
                    heap.emplace(-f[u], u);
                }
            }
            while (!heap.empty()) {
                auto [du, u] = heap.top();
                heap.pop();
                if (-du != f[u]) {
                    continue;
                }
                for (auto v : bg[u]) {
                    if (t[v] != 2) {
                        if (f[u] + 1 > max[v]) {
                            smx[v] = max[v];
                            max[v] = f[u] + 1;
                        } else if (f[u] + 1 > smx[v]) {
                            smx[v] = f[u] + 1;
                        }
                        if (smx[v] == -1) {
                            if (max[v] < f[v]) {
                                f[v] = max[v];
                                heap.emplace(-f[v], v);
                            }
                        } else if (smx[v] < f[v]) {
                            f[v] = smx[v];
                            heap.emplace(-f[v], v);
                        }
                    }
                }
            }
        } else {
            int u = scc[i][0];
            if (t[u] == 1) {
                int &a = max[u], &b = smx[u];
                for (auto v : adj[u]) {
                    if (bel[u] != bel[v]) {
                        if (f[v] + 1 > a) {
                            b = a;
                            a = f[v] + 1;
                        } else if (f[v] + 1 > b) {
                            b = f[v] + 1;
                        }
                    }
                }
                if (b == -1) {
                    f[u] = a;
                } else {
                    f[u] = b;
                }
            }
        }
        for (auto j : g[i]) {
            if (--deg[j] == 0) {
                que.push(j);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        // if (i == 2 && n == 169116 && m == 293138) {
        //     std::cout << t[i] << " " << scc[bel[i]].size() << "\n";
        //     int a = -1, b = -1;
        //     for (auto v : adj[i]) {
        //         if (bel[i] != bel[v]) {
        //             if (f[v] + 1 > a) {
        //                 b = a;
        //                 a = f[v] + 1;
        //             } else if (f[v] + 1 > b) {
        //                 b = f[v] + 1;
        //             }
        //         } else if (t[v] == 2) {
        //             if (inf > a) {
        //                 b = a;
        //                 a = inf;
        //             } else if (inf > b) {
        //                 b = inf;
        //             }
        //         }
        //     }
        //     std::cout << (b == -1 ? a : b) << "\n";
        // }
        if (f[i] >= inf / 2) {
            std::cout << "-1 ";
        } else {
            std::cout << f[i] << " ";
        }
    }

    return 0;
}
