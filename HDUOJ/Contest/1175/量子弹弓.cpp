#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> p(n);
    for (auto &p : p) {
        std::cin >> p;
    }

    if (std::find(p.begin(), p.end(), 0) != p.end()) {
        std::cout << "NO\n";
        return;
    }

    int dep = std::count(p.begin(), p.end(), 1);
    int sum = 0;
    for (auto p : p) {
        if (p > 1) {
            sum += p - 2;
        }
    }

    for (auto p : p) {
        if (p > 1 && p >= std::max(dep - (sum - (p - 2)), 1)) {
            std::cout << "YES\n";
            return;
        }
    }

    std::cout << "NO\n";
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
