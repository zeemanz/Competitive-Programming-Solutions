#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<u64> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    int m = std::min(n, 28);
    auto good = [&](u32 mask) { return (mask & (mask >> 1)) == 0; };
    auto full = [&](u32 mask) {
        for (int i = 0; i < m; i++) {
            if ((mask >> i & 1) == 0) {
                u32 cur = mask | (1 << i);
                if ((cur & (cur >> 1)) == 0) {
                    return false;
                }
            }
        }
        return true;
    };

    std::vector<u32> que;
    for (u32 mask = 0; mask < (1 << m); mask++) {
        if (good(mask) && full(mask)) {
            que.push_back(mask);
        }
    }

    std::vector pre(que.size(), std::vector<u64>());
    for (int i = 0; i < que.size(); i++) {
        u32 mask = que[i];
        std::vector<u64> cur(60);
        for (int j = 0; j < m; j++) {
            if (mask >> j & 1) {
                u64 x = a[j];
                for (int k = 59; k >= 0; k--) {
                    if (x >> k & 1) {
                        if (cur[k] == 0) {
                            cur[k] = x;
                            break;
                        }
                        x ^= cur[k];
                    }
                }
            }
        }
        for (auto x : cur) {
            if (x != 0) {
                pre[i].push_back(x);
            }
        }
        std::reverse(pre[i].begin(), pre[i].end());
    }

    auto query = [&](int i, u64 x) {
        for (auto y : pre[i]) {
            x = std::max(x, x ^ y);
        }
        return x;
    };

    u64 ans = 0;
    for (u32 mask = 0; mask < (1 << (n - m)); mask++) {
        if (good(mask)) {
            u64 cur = 0;
            for (int i = 0; i < n - m; i++) {
                if (mask >> i & 1) {
                    cur ^= a[m + i];
                }
            }
            for (int i = 0; i < que.size(); i++) {
                if (que[i] >> (m - 1) & 1 && mask & 1) {
                    continue;
                }
                ans = std::max(ans, query(i, cur));
            }
        }
    }

    std::cout << ans << "\n";
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
