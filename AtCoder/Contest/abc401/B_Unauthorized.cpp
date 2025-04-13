#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    int s = 0, c = 0;
    while (N--) {
        std::string o;
        std::cin >> o;

        if (o == "login") {
            s = 1;
        } else if (o == "logout") {
            s = 0;
        } else if (o == "private") {
            c += s == 0;
        }
    }
    std::cout << c << "\n";

    return 0;
}
