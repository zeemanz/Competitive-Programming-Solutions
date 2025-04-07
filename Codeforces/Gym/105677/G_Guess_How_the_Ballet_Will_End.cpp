#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 r;
    std::cin >> r;

    int n;
    std::cin >> n;

    i64 min = 0, max = r;
    for (int i = 0; i < n; i++) {
        i64 d;
        std::cin >> d;

        if (d < 0) {
            min = std::max(min + d, 0LL);
            max = std::max(max + d, 0LL);
        } else {
            min = std::min(min + d, r);
            max = std::min(max + d, r);
        }
    }

    if (min == max) {
        std::cout << min << "\n";
    } else {
        std::cout << "uncertain\n";
    }

    return 0;
}
