#include <bits/stdc++.h>

using u8 = unsigned char;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    const int B = std::sqrt(n);

    std::string s;
    std::cin >> s;

    std::vector<u8> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = s[i] - 'a';
    }

    auto f = [&](u8 x, u8 y) { return (6 - x - y) % 3; };

    auto dfs = [&](auto &&self, int x, int y) -> int {
        if (x == n - 1) {
            return a[y];
        }
        int d = 1;
        while (x + 3 * d < n) {
            d *= 3;
        }
        return f(self(self, x + d, y), self(self, x + d, y + d));
    };

    while (q--) {
        int x, y;
        std::cin >> x >> y;
        x--;
        y--;

        std::cout << char('a' + dfs(dfs, x, y));
    }

    return 0;
}
