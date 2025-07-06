#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<i64> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    std::vector<i64> s(n + 1);
    for (int i = 0; i < n; i++) {
        s[i + 1] = s[i] + a[i];
    }

    if (s[n] % 2) {
        std::cout << "-1\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        if (2 * a[i] > s[n]) {
            std::cout << "-1\n";
            return;
        }
    }

    for (int i = 0; i <= n; i++) {
        if (2 * s[i] == s[n]) {
            std::cout << "1\n";
            for (int j = 0; j < n; j++) {
                std::cout << a[j] << " \n"[j + 1 == n];
            }
            return;
        }
    }

    int p = 0;
    while (2 * s[p + 1] < s[n]) {
        p++;
    }

    i64 tot = s[p] + a[p] - s[n] / 2;
    std::vector<i64> b(n);
    for (int i = p - 1; i >= 0; i--) {
        i64 cur = std::min(tot, a[i]);
        b[i] = cur;
        tot -= cur;
    }
    b[p] = s[p] + a[p] - s[n] / 2;

    std::cout << "2\n";
    for (int i = 0; i < n; i++) {
        std::cout << b[i] << " \n"[i + 1 == n];
    }
    for (int i = 0; i < n; i++) {
        std::cout << a[i] - b[i] << " \n"[i + 1 == n];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
