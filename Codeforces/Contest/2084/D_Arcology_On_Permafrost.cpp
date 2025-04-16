#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;

    int f = std::max(std::min(n / (m + 1), n - m * k), k);
    for (int i = 0; i < n; i++) {
        std::cout << i % f << " \n"[i == n - 1];
    }
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
