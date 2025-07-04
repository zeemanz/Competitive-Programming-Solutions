#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<u32> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    std::vector<u64> s(n + 1);
    for (int i = 0; i < n; i++) {
        s[i + 1] = s[i] + a[i];
    }

    std::vector<u32> x(n + 1);
    for (int i = 0; i < n; i++) {
        x[i + 1] = x[i] ^ a[i];
    }

    std::vector<int> prev(n + 1, -1);
    std::vector<std::map<u32, int>> last(2);
    last[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        int o = i % 2;
        if (last[o ^ 1].contains(x[i])) {
            int j = last[o ^ 1][x[i]];
            prev[i] = j;
        }
        last[o][x[i]] = i;
    }

    while (q--) {
        int l, r;
        std::cin >> l >> r;
        l--;

        if (x[l] != x[r]) {
            std::cout << "-1\n";
        } else {
            if (s[l] == s[r]) {
                std::cout << "0\n";
            } else {
                if ((r - l) % 2 == 1) {
                    std::cout << "1\n";
                } else {
                    if (a[l] == 0 || a[r - 1] == 0) {
                        std::cout << "1\n";
                    } else if (prev[r] >= l) {
                        std::cout << "2\n";
                    } else {
                        std::cout << "-1\n";
                    }
                }
            }
        }
    }

    return 0;
}
