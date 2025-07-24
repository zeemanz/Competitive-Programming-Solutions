#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

f64 rand_real(f64 l = 0, f64 r = 1) {
    return std::uniform_real_distribution<f64>(l, r)(rng);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(12);

    int n;
    f64 k;
    std::cin >> n >> k;

    if (n >= 10) {
        std::cout << 1.0 << "\n";
        return 0;
    } else {
        auto work = [&](int n) {
            std::vector<std::vector<int>> adj(n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i == j) {
                        continue;
                    }
                    f64 x = rand_real();
                    if (x <= k) {
                        adj[i].push_back(j);
                    }
                }
            }
            int cur = 0, cnt = 0;
            std::vector<int> dfn(n, -1), low(n), stk, bel(n, -1);
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
                    int v;
                    do {
                        v = stk.back();
                        stk.pop_back();
                        bel[v] = cnt;
                    } while (v != u);
                    cnt++;
                }
            };
            for (int i = 0; i < n; i++) {
                if (dfn[i] == -1) {
                    dfs(dfs, i, -1);
                }
            }
            return cnt;
        };

        f64 sum = 0;
        for (int i = 0; i < (1 << 16); i++) {
            sum += work(n);
        }
        std::cout << sum / (1 << 16) << "\n";
    }

    return 0;
}
