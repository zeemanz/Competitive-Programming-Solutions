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
        std::string s;
        std::cin >> s;

        if (s.size() > 1 && s[0] == 'M' && s[1] == 'c') {
            ans++;
        }
    }

    std::cout << ans << "\n";

    return 0;
}
