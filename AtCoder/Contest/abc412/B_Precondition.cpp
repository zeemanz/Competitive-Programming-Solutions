#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s, t;
    std::cin >> s >> t;

    bool ok = true;
    std::set<char> v(t.begin(), t.end());
    for (int i = 1; i < s.size(); i++) {
        if (std::isupper(s[i])) {
            ok &= v.contains(s[i - 1]);
        }
    }

    if (ok) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    return 0;
}
