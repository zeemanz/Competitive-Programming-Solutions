#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int a, b;
        std::cin >> a >> b;

        ans += b > a;
    }

    std::cout << ans << "\n";

    return 0;
}
