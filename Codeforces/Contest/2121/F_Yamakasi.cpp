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
        int n, x;
        i64 s;
        std::cin >> n >> s >> x;

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        std::vector<i64> sum(n + 1);
        for (int i = 0; i < n; i++) {
            sum[i + 1] = sum[i] + a[i];
        }

        i64 ans = 0;
        std::map<i64, int> cnt, que;
        for (int i = 0; i <= n; i++) {
            ans += cnt[sum[i] - s];
            que[sum[i]]++;
            if (i < n) {
                if (a[i] > x) {
                    cnt.clear();
                    que.clear();
                } else if (a[i] == x) {
                    for (auto [k, v] : que) {
                        cnt[k] += v;
                    }
                    que.clear();
                }
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
