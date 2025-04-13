#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, L;
    std::cin >> n >> m >> L;

    std::vector<int> p(n);
    for (auto &p : p) {
        std::cin >> p;
    }
    std::ranges::sort(p);

    int max = p[0];
    for (int i = 0, j = 0; i < n; i++) {
        max = std::max(max, p[i] - j);
        j = p[i];
    }
    max = std::max(max, 2 * (L - p[n - 1]));

    std::vector<int> l(m);
    for (auto &l : l) {
        std::cin >> l;
    }
    std::ranges::sort(l);

    for (auto l : l) {
        if (2 * l >= max) {
            std::cout << l << "\n";
            return 0;
        }
    }
    std::cout << "-1\n";

    return 0;
}
