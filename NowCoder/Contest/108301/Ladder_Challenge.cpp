#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr int V = 1000000001, B = 30;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    const int m = std::__lg((n + B - 1) / B);
    std::vector f(m + 1, std::vector(n, 0)), g(m + 1, std::vector(n, V));
    for (int i = 0; i + B <= n; i++) {
        for (int j = i; j < i + B; j++) {
            f[0][i] = (f[0][i] + a[j] + 1) / 2;
        }
        int l = 0, r = a[i];
        while (r - l > 1) {
            int m = (l + r) / 2;
            int x = m;
            for (int j = i; j < i + B; j++) {
                x = (x + a[j] + 1) / 2;
            }
            if (x == f[0][i]) {
                l = m;
            } else {
                r = m;
            }
        }
        g[0][i] = r;
    }
    for (int j = 0; j < m; j++) {
        for (int i = 0; i + B * (2 << j) <= n; i++) {
            f[j + 1][i] = f[j][i + B * (1 << j)] + (f[j][i] >= g[j][i + B * (1 << j)]);
            if (f[j][i] + 1 == g[j][i + B * (1 << j)]) {
                g[j + 1][i] = g[j][i];
            }
        }
    }

    while (q--) {
        int x, y;
        std::cin >> x >> y;
        y--;

        int l = std::upper_bound(a.begin(), a.end(), x) - a.begin();
        int r = n - y;
        int v = x;
        for (int i = m; i >= 0; i--) {
            if (l + B * (1 << i) < r) {
                v = f[i][l] + (v >= g[i][l]);
                l += B * (1 << i);
            }
        }
        while (l < r) {
            v = (v + a[l] + 1) / 2;
            l++;
        }

        std::cout << v - x << "\n";
    }

    return 0;
}
