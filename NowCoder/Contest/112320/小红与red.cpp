#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    for (int i = 1; i < n; i++) {
        if (s[i] == s[i - 1]) {
            for (auto c : {'r', 'e', 'd'}) {
                if (c != s[i - 1] && (i + 1 == n || c != s[i + 1])) {
                    s[i] = c;
                    break;
                }
            }
        }
    }

    std::cout << s << "\n";

    return 0;
}
