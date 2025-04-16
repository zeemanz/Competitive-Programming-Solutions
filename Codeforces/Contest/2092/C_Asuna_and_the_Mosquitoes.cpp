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

        int cnt[2]{};
        i64 sum[2]{};
        for (auto a : a) {
            cnt[a % 2]++;
            sum[a % 2] += a;
        }

        i64 ans = *std::ranges::max_element(a);
        if (cnt[0] > 0 && cnt[1] > 0) {
            ans = std::max(ans, sum[0] + sum[1] - cnt[1] + 1);
        }

        std::cout << ans << "\n";
    }

    return 0;
}
