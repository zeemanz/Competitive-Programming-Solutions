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
        int n, q;
        std::cin >> n >> q;

        while (q--) {
            std::string o;
            std::cin >> o;

            if (o == "->") {
                int x, y;
                std::cin >> x >> y;
                x--;
                y--;

                i64 d = 0;
                for (i64 i = 1, j = 1; i <= (1LL << (2 * n - 2)); i *= 4, j *= 2) {
                    int a = x & 1;
                    int b = y & 1;
                    if (a == 0 && b == 0) {
                    } else if (a == 0 && b == 1) {
                        d = 3 * i + d;
                    } else if (a == 1 && b == 0) {
                        d = 2 * i + d;
                    } else {
                        d = i + d;
                    }
                    x /= 2;
                    y /= 2;
                }
                std::cout << d + 1 << "\n";
            } else {
                i64 d;
                std::cin >> d;
                d--;

                int x = 1, y = 1;
                for (i64 i = 1LL << (2 * n - 2), j = 1 << (n - 1); i > 0; i /= 4, j /= 2) {
                    x += ((d / i) % 3 != 0) * j;
                    y += ((d / i) % 2 != 0) * j;
                    d %= i;
                }
                std::cout << x << " " << y << "\n";
            }
        }
    }

    return 0;
}
