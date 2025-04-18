#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }

    do {
        for (int i = 0; i < n; i++) {
            std::cout << char('A' + p[i]);
            if (i + 1 < n) {
                std::cout << "+";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "Problem\n";
    } while (std::next_permutation(p.begin(), p.end()));

    return 0;
}
