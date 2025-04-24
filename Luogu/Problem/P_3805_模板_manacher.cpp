#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

std::vector<int> manacher(const std::string &s) {
    std::string t{0};
    for (auto c : s) {
        t.push_back(c);
        t.push_back(0);
    }
    int n = t.size();
    std::vector<int> d(n);
    for (int i = 0, p = 0; i < n; i++) {
        if (p - (i - p) >= 0 && p + d[p] > i) {
            d[i] = std::min(d[p - (i - p)], p + d[p] - i);
        }
        while (i - d[i] >= 0 && i + d[i] < n && t[i - d[i]] == t[i + d[i]]) {
            d[i]++;
        }
        if (i + d[i] > p + d[p]) {
            p = i;
        }
    }
    return d;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;

    auto d = manacher(s);
    std::cout << *std::max_element(d.begin(), d.end()) - 1 << "\n";

    return 0;
}
