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

        int lo = 1, hi = n;
        std::vector<int> a;
        for (int i = n - 2; i >= 0; i--) {
            if (s[i] == '>') {
                a.push_back(hi);
                hi--;
            } else {
                a.push_back(lo);
                lo++;
            }
        }
        a.push_back(lo);

        std::reverse(a.begin(), a.end());
        for (auto a : a) {
            std::cout << a << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
