#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::string s, t;
    std::cin >> s >> t;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'o' && t[i] == 'o') {
            std::cout << "Yes\n";
            return 0;
        }
    }
    std::cout << "No\n";

    return 0;
}
