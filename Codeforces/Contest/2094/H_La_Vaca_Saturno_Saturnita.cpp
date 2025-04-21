#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr int V = 1E5;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<int>> d(V + 1);
    for (int i = 2; i <= V; i++) {
        for (int j = i; j <= V; j += i) {
            d[j].push_back(i);
        }
    }

    int t;
    std::cin >> t;

    while (t--) {
        int n, q;
        std::cin >> n >> q;

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        std::map<int, std::vector<int>> pos;
        for (int i = 0; i < n; i++) {
            pos[a[i]].push_back(i);
        }

        while (q--) {
            int k, l, r;
            std::cin >> k >> l >> r;
            l--;

            i64 ans = 0;
            for (int i = l; i < r;) {
                while (k % a[i] == 0) {
                    k /= a[i];
                }
                int j = r;
                for (auto d : d[k]) {
                    auto it = std::ranges::upper_bound(pos[d], i);
                    if (it != pos[d].end()) {
                        j = std::min(j, *it);
                    }
                }
                ans += 1LL * (j - i) * k;
                i = j;
            }
            std::cout << ans << "\n";
        }
    }

    return 0;
}
