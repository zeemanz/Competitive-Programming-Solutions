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
    std::sort(a.begin(), a.end());

    int lo = 0, hi = 1E9;
    while (lo < hi) {
        int x = (lo + hi + 1) / 2;
        int c = std::lower_bound(a.begin(), a.end(), x) - a.begin();
        if (n - c >= x) {
            lo = x;
        } else {
            hi = x - 1;
        }
    }
    std::cout << lo << "\n";

    return 0;
}
