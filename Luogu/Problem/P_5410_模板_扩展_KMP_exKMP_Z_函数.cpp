#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

std::vector<int> zFunction(const std::string &s) {
    int n = s.size();
    std::vector<int> z(n);
    for (int i = 1, j = 1; i < n; i++) {
        z[i] = std::max(std::min(z[i - j], j + z[j] - i), 0);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > j + z[j]) {
            j = i;
        }
    }
    return z;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string a, b;
    std::cin >> a >> b;

    auto z = zFunction(b);
    z[0] = z.size();
    auto p = zFunction(b + "|" + a);
    p[0] = p.size();

    i64 x = 0, y = 0;
    for (int i = 0; i < z.size(); i++) {
        x ^= 1LL * (i + 1) * (z[i] + 1);
    }
    for (int i = b.size() + 1; i < p.size(); i++) {
        y ^= 1LL * (i - b.size()) * (p[i] + 1);
    }

    std::cout << x << "\n";
    std::cout << y << "\n";

    return 0;
}
