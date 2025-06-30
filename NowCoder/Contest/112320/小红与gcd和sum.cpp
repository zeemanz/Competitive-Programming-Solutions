#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    std::map<int, int> cnt;
    for (auto a : a) {
        cnt[a]++;
    }

    i64 ans = 0;
    for (auto [k, v] : cnt) {
        ans = std::max(ans, 1LL * k * v * k);
    }

    std::cout << ans << "\n";

    return 0;
}
