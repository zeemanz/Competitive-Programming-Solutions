#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;

    for (auto c : s) {
        if (c == 'O') {
            std::cout << ".-.-";
        } else {
            std::cout << ".-";
        }
    }
    std::cout << "\n";

    return 0;
}
