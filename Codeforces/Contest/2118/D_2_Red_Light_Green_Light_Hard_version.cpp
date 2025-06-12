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
        i64 k;
        std::cin >> n >> k;

        std::vector<i64> p(n);
        for (auto &p : p) {
            std::cin >> p;
        }

        std::vector<i64> d(n);
        for (auto &d : d) {
            std::cin >> d;
        }

        std::vector<i64> f(n), g(n);
        for (int i = 0; i < n; i++) {
            f[i] = (p[i] + k - d[i]) % k;
            g[i] = (p[i] + d[i]) % k;
        }

        std::vector<int> deg(2 * n);
        std::vector<std::vector<int>> adj(2 * n);

        std::map<i64, int> s;
        for (int i = 0; i < n; i++) {
            if (s.contains(g[i])) {
                int j = s[g[i]];
                adj[2 * j + 1].push_back(2 * i);
                deg[2 * i]++;
            }
            s[g[i]] = i;
        }
        s.clear();
        for (int i = 0; i < n; i++) {
            if (s.contains(f[i])) {
                int j = s[f[i]];
                adj[2 * i].push_back(2 * j + 1);
                deg[2 * j + 1]++;
            }
            s[f[i]] = i;
        }

        std::vector<int> ok(2 * n);
        std::queue<i64> que;
        for (int i = 0; i < 2 * n; i++) {
            if (deg[i] == 0) {
                ok[i] = 1;
                que.push(i);
            }
        }
        while (!que.empty()) {
            auto u = que.front();
            que.pop();
            for (auto v : adj[u]) {
                deg[v]--;
                ok[v] |= ok[u];
                if (deg[v] == 0) {
                    que.push(v);
                }
            }
        }

        std::map<i64, int> pos;
        std::map<i64, std::vector<i64>> occ;
        for (int i = 0; i < n; i++) {
            pos[p[i]] = i;
            occ[f[i]].push_back(p[i]);
        }

        int q;
        std::cin >> q;

        while (q--) {
            i64 s;
            std::cin >> s;

            if (!occ.contains(s % k)) {
                std::cout << "YES\n";
                continue;
            }

            auto it = std::lower_bound(occ[s % k].begin(), occ[s % k].end(), s);
            if (it == occ[s % k].end()) {
                std::cout << "YES\n";
                continue;
            }

            int i = pos[*it];
            if (ok[2 * i]) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }
    }

    return 0;
}
