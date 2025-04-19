#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n;
    std::cin >> n;

    std::map<int, int> X, Y;
    for (int i = 0; i < n; i++) {
        int x, y;
        std::cin >> x >> y;

        X[x]++;
        Y[x + y]++;
    }

    int x = 0, y = 0;
    for (auto [k, v] : X) {
        if (v % 2) {
            x = k;
        }
    }
    for (auto [k, v] : Y) {
        if (v % 2) {
            y = k;
        }
    }
    std::cout << x << " " << y - x << "\n";
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
