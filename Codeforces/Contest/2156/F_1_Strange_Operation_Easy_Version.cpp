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

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
            a--;
        }

        std::vector<int> pos(n);
        for (int i = 0; i < n; i++) {
            pos[a[i]] = i;
        }

        std::vector<int> vis(n);
        std::priority_queue<int, std::vector<int>, std::greater<>> que;
        for (int x = 2; x < n; x++) {
            if (pos[x] < std::min(pos[x - 1], pos[x - 2])) {
                vis[x] = 1;
                que.push(x);
            }
        }

        while (!que.empty()) {
            int x = que.top();
            que.pop();
            vis[x] = 0;

            int i = pos[x];
            int j = pos[x - 1];
            int k = pos[x - 2];
            a[i] -= 2;
            a[j] += 1;
            a[k] += 1;
            pos[a[i]] = i;
            pos[a[j]] = j;
            pos[a[k]] = k;

            for (int x = std::max(a[i], 2); x < std::min(std::max(a[j], a[k]) + 3, n); x++) {
                if (!vis[x] && pos[x] < std::min(pos[x - 1], pos[x - 2])) {
                    vis[x] = 1;
                    que.push(x);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            std::cout << a[i] + 1 << " \n"[i + 1 == n];
        }
    }

    return 0;
}
