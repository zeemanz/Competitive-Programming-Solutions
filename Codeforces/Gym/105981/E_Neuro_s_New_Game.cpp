#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    if (s == std::string(n, '0') || s == std::string(n, '1')) {
        std::cout << "-1\n";
        return 0;
    }

    std::set<int> v;
    for (int i = 0; i < n; i++) {
        v.insert(i);
    }

    auto prev = [&](int i) { return (i + n - 1) % n; };
    auto next = [&](int i) { return (i + 1) % n; };

    std::vector<int> a(n, -1);
    for (int i = 0; i < n; i++) {
        if (s[prev(i)] == '1' && s[i] == '0') {
            for (int j = i; a[j] == -1; j = next(j)) {
                if (s[j] == '0') {
                    a[j] = *v.begin();
                    v.erase(a[j]);
                }
            }
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        if (s[prev(i)] == '0' && s[i] == '1') {
            for (int j = i; !v.empty(); j = next(j)) {
                if (s[j] == '1') {
                    a[j] = *v.rbegin();
                    v.erase(a[j]);
                }
            }
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " \n"[i + 1 == n];
    }

    return 0;
}
