#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> f(n);
    for (auto &f : f) {
        std::cin >> f;
    }

    std::vector a(n, std::vector(n, -1));
    for (int i = 0; i < n; i++) {
        std::vector<int> v(n);
        for (int j = 0; j < n; j++) {
            if (a[i][j] != -1) {
                v[a[i][j]] = 1;
            }
        }
        std::vector<int> p;
        for (int m = 1; m < f[i]; m++) {
            if (!v[m]) {
                int j = i;
                if (!p.empty()) {
                    j = p.back();
                    p.pop_back();
                }
                a[i][j] = m;
                a[j][i] = m;
            }
            if (a[i][m - 1] == -1) {
                p.push_back(m - 1);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == -1) {
                a[i][j] = 0;
            }
            std::cout << a[i][j] << " \n"[j + 1 == n];
        }
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
