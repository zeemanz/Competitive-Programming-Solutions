#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> deg(n);
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        int c;
        std::cin >> c;
        while (c--) {
            int j;
            std::cin >> j;
            j--;
            adj[i].push_back(j);
            deg[j]++;
        }
    }

    if (std::count(deg.begin(), deg.end(), 0) != 1) {
        std::cout << "0\n";
    } else {
        int s = std::find(deg.begin(), deg.end(), 0) - deg.begin();
        std::queue<int> que;
        que.push(s);
        std::vector<int> dis(n);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (auto v : adj[u]) {
                dis[v] = std::max(dis[v], dis[u] + 1);
                if (--deg[v] == 0) {
                    que.push(v);
                }
            }
        }
        if (std::find(dis.begin(), dis.end(), n - 1) != dis.end()) {
            std::cout << "1\n";
        } else {
            std::cout << "0\n";
        }
    }

    return 0;
}
