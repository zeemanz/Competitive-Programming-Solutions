#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

template <class T, T inf, class C = std::less<>> struct LiChaoSegmentTree {
    static constexpr C cmp = {};
    struct Line {
        T k, b;
        constexpr Line(T k = 0, T b = std::max(-inf, inf, cmp)) : k{k}, b{b} {}
        constexpr T operator()(T x) const {
            return k * x + b;
        }
    };
    struct Node {
        Node *l, *r;
        Line f;
        Node() : l{}, r{}, f{} {}
    };
    int n;
    Node *t;
    LiChaoSegmentTree(int n = 0) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        t = nullptr;
    }
    void insert(Node *&p, int l, int r, int x, int y, Line f) {
        if (l >= y || r <= x) {
            return;
        }
        if (p == nullptr) {
            p = new Node();
        }
        int m = (l + r) / 2;
        if (l >= x && r <= y) {
            if (cmp(f(m), p->f(m))) {
                std::swap(f, p->f);
            }
            if (r - l == 1) {
                return;
            }
            if (cmp(f(l), p->f(l))) {
                insert(p->l, l, m, x, y, f);
            } else {
                insert(p->r, m, r, x, y, f);
            }
        } else {
            insert(p->l, l, m, x, y, f);
            insert(p->r, m, r, x, y, f);
        }
    }
    void insert(int l, int r, Line f) {
        insert(t, 0, n, l, r, f);
    }
    void insert(Line f) {
        insert(t, 0, n, 0, n, f);
    }
    T query(Node *p, int l, int r, int x) {
        if (p == nullptr) {
            return Line()(x);
        }
        if (r - l == 1) {
            return p->f(x);
        }
        int m = (l + r) / 2;
        if (x < m) {
            return std::min(p->f(x), query(p->l, l, m, x), cmp);
        } else {
            return std::min(p->f(x), query(p->r, m, r, x), cmp);
        }
    }
    T query(int x) {
        return query(t, 0, n, x);
    }
};

constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, m;
        std::cin >> n >> m;

        std::vector<std::array<i64, 4>> edges;
        std::vector<std::vector<std::pair<int, i64>>> g(n), h(n);
        for (int i = 0; i < m; i++) {
            int u, v, w;
            i64 t;
            std::cin >> u >> v >> t >> w;
            u--, v--;

            edges.push_back({u, v, t, w});
            g[u].emplace_back(v, t);
            h[v].emplace_back(u, t);
        }

        auto dijkstra = [&](int s, const std::vector<std::vector<std::pair<int, i64>>> &adj) {
            std::vector<i64> dis(n, inf);
            dis[s] = 0;
            std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>, std::greater<>> que;
            que.emplace(0, s);
            while (!que.empty()) {
                auto [d, u] = que.top();
                que.pop();
                if (d != dis[u]) {
                    continue;
                }
                for (auto [v, t] : adj[u]) {
                    if (dis[v] > dis[u] + t) {
                        dis[v] = dis[u] + t;
                        que.emplace(dis[v], v);
                    }
                }
            }
            return dis;
        };

        std::vector<std::vector<i64>> dis(n);
        dis[0] = dijkstra(0, g);
        dis[n - 1] = dijkstra(n - 1, h);

        LiChaoSegmentTree<i64, inf> seg(int(1E9) + 1);
        for (auto [u, v, t, w] : edges) {
            seg.insert({-w, dis[0][u] + dis[n - 1][v] + t});
        }

        int q;
        std::cin >> q;

        while (q--) {
            int k;
            std::cin >> k;

            std::cout << seg.query(k) << "\n";
        }
    }

    return 0;
}
