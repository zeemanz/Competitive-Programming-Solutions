#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::map<std::string, int> v;
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        v[s]++;
    }

    int max = 0;
    for (auto [k, v] : v) {
        max = std::max(max, v);
    }

    for (auto [k, v] : v) {
        if (v == max) {
            std::cout << k << "\n";
            break;
        }
    }

    return 0;
}
