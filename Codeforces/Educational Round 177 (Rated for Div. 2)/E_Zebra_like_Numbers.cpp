#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    u64 l, r, k;
    std::cin >> l >> r >> k;

    auto get = [&](u64 x) {
        u64 v = (3 * x + k) / 4;
        std::vector<u32> a;
        while (v > 0) {
            a.push_back(v % 4);
            v /= 4;
        }
        std::vector mem(a.size(), std::vector(2, std::vector(2, std::map<u64, u64>())));
        auto dfs = [&](auto &&self, int cur, bool lim, bool has, u64 sum) -> u64 {
            if (cur == -1) {
                return sum == k;
            }
            if (mem[cur][lim][has].contains(sum)) {
                return mem[cur][lim][has][sum];
            }
            u32 up = has ? 0 : (lim ? a[cur] : 4);
            u64 res = 0;
            for (u32 x = 0; x <= up; x++) {
                res += self(self, cur - 1, lim && x == a[cur], has || x == 4, sum + x);
            }
            return mem[cur][lim][has][sum] = res;
        };
        return dfs(dfs, a.size() - 1, true, false, 0);
    };

    std::cout << get(r) - get(l - 1) << "\n";
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
