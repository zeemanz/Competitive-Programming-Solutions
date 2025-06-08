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

        for (int i = 0; i + 1 < n; i++) {
            if (s[i + 1] < s[i]) {
                int j = i;
                while (j + 1 < n && s[j + 1] <= s[j]) {
                    std::swap(s[j], s[j + 1]);
                    j++;
                }
                break;
            }
        }

        std::cout << s << "\n";
    }

    return 0;
}
