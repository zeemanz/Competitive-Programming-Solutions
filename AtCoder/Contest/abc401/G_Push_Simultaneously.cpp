#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = double;

constexpr f64 eps = 1E-9;

int sgn(f64 x) {
    if (std::fabs(x) < eps) {
        return 0;
    } else {
        return x < 0 ? -1 : 1;
    }
}

struct MaxFlow {
    using flow_t = int;
    struct Edge {
        int to;
        flow_t cap;
        Edge(int to, flow_t cap) : to{to}, cap{cap} {}
    };
    int n;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> list;
    std::vector<int> dis, cur;
    MaxFlow(int n = 0) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        edges.clear();
        list.assign(n, {});
    }
    void addEdge(int u, int v, flow_t c) {
        list[u].push_back(edges.size());
        edges.emplace_back(v, c);
        list[v].push_back(edges.size());
        edges.emplace_back(u, 0);
    }
    bool bfs(int s, int t) {
        dis.assign(n, -1);
        std::queue<int> que;
        dis[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int i : list[u]) {
                auto [v, c] = edges[i];
                if (c > 0 && dis[v] == -1) {
                    dis[v] = dis[u] + 1;
                    if (v == t) {
                        return true;
                    }
                    que.push(v);
                }
            }
        }
        return false;
    }
    flow_t dfs(int u, int t, flow_t f) {
        if (u == t) {
            return f;
        }
        auto r = f;
        for (int &i = cur[u]; i < list[u].size(); i++) {
            int j = list[u][i];
            auto [v, c] = edges[j];
            if (c > 0 && dis[v] == dis[u] + 1) {
                auto u = dfs(v, t, std::min(r, c));
                edges[j].cap -= u;
                edges[j ^ 1].cap += u;
                r -= u;
                if (r == 0) {
                    return f;
                }
            }
        }
        return f - r;
    }
    flow_t flow(int s, int t) {
        flow_t res = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            res += dfs(s, t, std::numeric_limits<flow_t>::max());
        }
        return res;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(12);

    int N;
    std::cin >> N;

    std::vector<std::pair<i64, i64>> p(N), q(N);
    for (auto &[x, y] : p) {
        std::cin >> x >> y;
    }
    for (auto &[x, y] : q) {
        std::cin >> x >> y;
    }

    int s = 2 * N, t = s + 1;
    MaxFlow g(t + 1);

    f64 lo = 0, hi = 2E18;
    for (int r = 0; r < 128; r++) {
        g.init(t + 1);
        f64 x = (lo + hi) / 2;
        for (int i = 0; i < N; i++) {
            auto [px, py] = p[i];
            for (int j = 0; j < N; j++) {
                auto [qx, qy] = q[j];
                if (sgn(x - std::hypot(px - qx, py - qy)) >= 0) {
                    g.addEdge(i, N + j, 1);
                }
            }
        }
        for (int i = 0; i < N; i++) {
            g.addEdge(s, i, 1);
            g.addEdge(N + i, t, 1);
        }
        if (g.flow(s, t) == N) {
            hi = x;
        } else {
            lo = x;
        }
    }
    std::cout << lo << "\n";

    return 0;
}
