#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<i64> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        i64 min = *std::min_element(a.begin(), a.end());
        int cnt = std::count(a.begin(), a.end(), min);

        if (cnt > 1) {
            std::cout << "Yes\n";
        } else {
            i64 gcd = 0;
            for (auto a : a) {
                if (a > min && a % min == 0) {
                    gcd = std::gcd(gcd, a);
                }
            }
            if (gcd == min) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        }
    }

    return 0;
}
