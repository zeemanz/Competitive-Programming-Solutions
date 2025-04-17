#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;

    int n = s.size();
    std::vector<int> f(n + 1);
    for (int l = 0, r = n - 1; l <= r; l++, r--) {
        if (l < r - 1 && s[l] == s[r - 1]) {
            f[r]++;
            f[n]--;
        }
        if (l < r && s[l] == s[r]) {
            f[l + 1]++;
            f[r]--;
        }
        if (l < r + 1 && s[l] == s[r + 1]) {
            f[0]++;
            f[l]--;
        }
    }
    for (int i = 0; i < n; i++) {
        f[i + 1] += f[i];
    }
    std::cout << std::count(f.begin(), f.end(), (n - 1) / 2) << "\n";

    return 0;
}
