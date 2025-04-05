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
        int n, m, k;
        std::cin >> n >> m >> k;

        if (k > std::max(n, m) || k < std::max(n, m) - std::min(n, m)) {
            std::cout << "-1\n";
            continue;
        }

        int x = 0, y = 1;
        if (n < m) {
            std::swap(x, y);
            std::swap(n, m);
        }

        std::vector<int> s;
        for (int i = 0; i < k; i++) {
            s.push_back(x);
            n--;
        }
        while (n > 0) {
            s.push_back(y);
            s.push_back(x);
            n--;
            m--;
        }
        while (m > 0) {
            s.push_back(y);
            m--;
        }

        for (int i = 0; i < s.size(); i++) {
            std::cout << s[i];
        }
        std::cout << "\n";
    }

    return 0;
}
