#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    int ans = 0;
    std::vector<int> c(n + 1);

    while (q--) {
        int i;
        std::cin >> i;
        i--;

        if (i > 0) {
            ans -= (c[i - 1] ^ c[i]) & c[i - 1];
        }
        ans -= (c[i] ^ c[i + 1]) & c[i];

        c[i] ^= 1;

        if (i > 0) {
            ans += (c[i - 1] ^ c[i]) & c[i - 1];
        }
        ans += (c[i] ^ c[i + 1]) & c[i];

        std::cout << ans << "\n";
    }

    return 0;
}
