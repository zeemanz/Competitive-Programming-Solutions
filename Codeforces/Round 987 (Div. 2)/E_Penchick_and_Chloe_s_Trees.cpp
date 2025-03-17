#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> p(n, -1);
    for (int i = 1; i < n; i++) {
        std::cin >> p[i];
        p[i]--;
    }

    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        adj[p[i]].push_back(i);
    }

    auto dfs = [&](auto &&self, int x) -> int {
        std::vector<int> a;
        for (auto y : adj[x]) {
            a.push_back(self(self, y));
        }
        std::priority_queue<int, std::vector<int>, std::greater<>> que;
        for (auto a : a) {
            que.push(a);
        }
        while (que.size() > 2) {
            int x = que.top();
            que.pop();
            int y = que.top();
            que.pop();
            que.push(y + 1);
        }
        int res = 0;
        while (!que.empty()) {
            res = std::max(res, que.top() + 1);
            que.pop();
        }
        return res;
    };

    std::cout << dfs(dfs, 0) << "\n";
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
