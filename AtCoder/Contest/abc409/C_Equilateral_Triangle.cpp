#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, L;
    std::cin >> n >> L;

    std::vector<int> d(n);
    for (int i = 1; i < n; i++) {
        std::cin >> d[i];
    }

    std::vector<int> a(n);
    for (int i = 1; i < n; i++) {
        a[i] = (a[i - 1] + d[i]) % L;
    }

    std::vector<int> cnt(L);
    for (auto a : a) {
        cnt[a]++;
    }

    i64 ans = 0;
    if (L % 3 == 0) {
        for (int i = 0; i < L / 3; i++) {
            int j = (i + L / 3) % L;
            int k = (j + L / 3) % L;
            ans += 1LL * cnt[i] * cnt[j] * cnt[k];
        }
    }
    std::cout << ans << "\n";

    return 0;
}
