#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    std::vector<int> w(17);
    for (auto &w : w) {
        std::cin >> w;
    }

    int m;
    std::cin >> m;

    if (m % 2) {
        m++;
    }

    std::vector<int> ok(1 << 17, 1);
    for (int i = 0; i + m <= n; i++) {
        u32 mask = 0;
        for (int j = 0; j < m / 2; j++) {
            if (s[i + j] != s[i + m - j - 1]) {
                int k = std::min(s[i + j], s[i + m - j - 1]) - 'a';
                mask |= 1 << k;
            } else {
                mask = 0;
                break;
            }
        }
        if (mask > 0) {
            ok[mask] = 0;
        }
    }
    for (int i = 0; i < 17; i++) {
        for (u32 mask = 0; mask < (1 << 17); mask++) {
            if (mask >> i & 1) {
                ok[mask] &= ok[mask ^ (1 << i)];
            }
        }
    }

    int ans = std::accumulate(w.begin(), w.end(), 0);
    for (u32 mask = 0; mask < (1 << 17); mask++) {
        if (ok[mask]) {
            int sum = 0;
            for (int i = 0; i < 17; i++) {
                if (~mask >> i & 1) {
                    sum += w[i];
                }
            }
            ans = std::min(ans, sum);
        }
    }

    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
