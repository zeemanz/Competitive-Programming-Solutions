#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr int inf = 1E9;

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
        }

        auto check = [&](int x) {
            std::vector<int> stk;
            std::vector<std::vector<int>> adj(n);
            for (int i = 0; i < n; i++) {
                for (auto j : stk) {
                    if (a[i] - a[j] >= x) {
                        adj[i].push_back(j);
                        adj[j].push_back(i);
                    }
                }
                stk.push_back(i);
                for (int j = stk.size() - 1; j > 0; j--) {
                    if (a[stk[j - 1]] > a[stk[j]]) {
                        std::swap(stk[j - 1], stk[j]);
                    }
                }
                if (stk.size() > 3) {
                    stk.pop_back();
                }
            }
            int tot = 0;
            for (int i = 0; i < n; i++) {
                tot += adj[i].size() >= 2;
            }
            for (int i = 0; i < n; i++) {
                int cnt = adj[i].size() >= 2;
                for (int j : adj[i]) {
                    cnt += adj[j].size() == 2;
                }
                if (cnt == tot) {
                    return false;
                }
            }
            return true;
        };

        int lo = 1 - inf, hi = inf;
        while (hi - lo > 1) {
            int md = std::midpoint(lo, hi);
            if (check(md)) {
                lo = md;
            } else {
                hi = md;
            }
        }

        std::cout << lo << "\n";
    }

    return 0;
}
