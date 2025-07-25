#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> b(n), c(n);
    for (auto &b : b) {
        std::cin >> b;
    }
    for (auto &c : c) {
        std::cin >> c;
    }

    for (int i = 1; i < n; i++) {
        b[i] = std::max(b[i - 1], b[i]);
        if (b[i] > c[i]) {
            std::cout << "NO\n";
            return;
        }
    }

    i64 sum = std::accumulate(b.begin(), b.end(), 0LL);
    if (sum > m) {
        std::cout << "NO\n";
        return;
    }

    i64 add = 0;
    for (int i = n - 1; i >= 0; i--) {
        add += c[i] - b[i];
        if (i > 0) {
            c[i - 1] = std::min(c[i - 1], c[i]);
        }
    }

    if (sum + add >= m) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
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
