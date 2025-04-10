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
        std::string s;
        std::cin >> s;

        int i = s.size() - 1;
        while (s[i] == '0') {
            i--;
        }
        std::cout << s.size() - std::count(s.begin(), s.begin() + i, '0') - 1 << "\n";
    }

    return 0;
}
