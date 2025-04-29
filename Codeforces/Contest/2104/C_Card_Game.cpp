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

        if (n == 2) {
            if (s[0] == 'A') {
                std::cout << "Alice\n";
            } else {
                std::cout << "Bob\n";
            }
        } else {
            if (s[0] == 'A' && s[n - 1] == 'A') {
                std::cout << "Alice\n";
            } else if (s[n - 2] == 'A' && s[n - 1] == 'A') {
                std::cout << "Alice\n";
            } else if (s[n - 1] == 'B' && std::count(s.begin(), s.end(), 'B') == 1) {
                std::cout << "Alice\n";
            } else {
                std::cout << "Bob\n";
            }
        }
    }

    return 0;
}
