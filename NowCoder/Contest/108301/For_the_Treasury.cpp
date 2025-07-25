#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k, c;
    std::cin >> n >> k >> c;

    std::vector<i64> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    for (int i = 0; i < n; i++) {
        a[i] -= 1LL * c * (i + 1);
    }
    std::sort(a.begin(), a.end(), std::greater());

    i64 ans = std::accumulate(a.begin(), a.begin() + k, 0LL);
    ans += 1LL * c * k * (k + 1) / 2;

    std::cout << ans << "\n";

    return 0;
}
