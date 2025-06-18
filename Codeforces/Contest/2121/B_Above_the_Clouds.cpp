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

        std::string s;
        std::cin >> s;

        bool ok = false;
        for (char c = 'a'; c <= 'z'; c++) {
            int x = std::count(s.begin(), s.end(), c);
            int y = std::count(s.begin() + 1, s.end() - 1, c);
            ok |= x > 1 && y > 0;
        }

        if (ok) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }

    return 0;
}
