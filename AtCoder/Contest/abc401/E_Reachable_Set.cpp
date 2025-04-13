#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

struct DSU {
    std::vector<int> par;
    DSU() {}
    DSU(int n) {
        init(n);
    }
    void init(int n) {
        par.resize(n);
        std::iota(par.begin(), par.end(), 0);
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
        return true;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> adj(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<int> v(N);
    for (int i = N - 1; i > 0; i--) {
        if (!adj[i].empty()) {
            int j = *std::ranges::min_element(adj[i]);
            if (j < i) {
                v[j]++;
            }
        }
    }

    int s = 0, c = 0;
    DSU dsu(N);
    for (int i = 0; i < N; i++) {
        s += v[i];
        c++;
        if (!adj[i].empty()) {
            int j = *std::ranges::min_element(adj[i]);
            if (j < i) {
                s--;
            }
        }
        for (int j : adj[i]) {
            if (j < i) {
                c -= dsu.merge(i, j);
            }
        }
        if (c == 1) {
            std::cout << s << "\n";
        } else {
            std::cout << "-1\n";
        }
    }

    return 0;
}
