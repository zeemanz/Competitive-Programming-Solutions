#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector h(n, std::vector(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cin >> h[i][j];
            }
        }

        std::vector<int> a(n), b(n);
        for (auto &a : a) {
            std::cin >> a;
        }
        for (auto &b : b) {
            std::cin >> b;
        }

        std::vector f(n, std::vector(2, std::vector(2, 1)));
        for (int i = 0; i + 1 < n; i++) {
            for (int j = 0; j < n; j++) {
                int d = h[i][j] - h[i + 1][j];
                if (d == -1) {
                    f[i][1][0] = 0;
                } else if (d == 0) {
                    f[i][0][0] = 0;
                    f[i][1][1] = 0;
                } else if (d == 1) {
                    f[i][0][1] = 0;
                }
            }
        }

        std::vector g(n, std::vector(2, std::vector(2, 1)));
        for (int j = 0; j + 1 < n; j++) {
            for (int i = 0; i < n; i++) {
                int d = h[i][j] - h[i][j + 1];
                if (d == -1) {
                    g[j][1][0] = 0;
                } else if (d == 0) {
                    g[j][0][0] = 0;
                    g[j][1][1] = 0;
                } else if (d == 1) {
                    g[j][0][1] = 0;
                }
            }
        }

        i64 X[2]{0, a[0]};
        for (int i = 0; i + 1 < n; i++) {
            i64 nX[2]{inf, inf};
            for (int c : {0, 1}) {
                for (int d : {0, 1}) {
                    if (f[i][c][d]) {
                        nX[d] = std::min(nX[d], X[c] + d * a[i + 1]);
                    }
                }
            }
            std::swap(X, nX);
        }

        i64 Y[2]{0, b[0]};
        for (int j = 0; j + 1 < n; j++) {
            i64 nY[2]{inf, inf};
            for (int c : {0, 1}) {
                for (int d : {0, 1}) {
                    if (g[j][c][d]) {
                        nY[d] = std::min(nY[d], Y[c] + d * b[j + 1]);
                    }
                }
            }
            std::swap(Y, nY);
        }

        i64 ans = std::min(X[0], X[1]) + std::min(Y[0], Y[1]);
        if (ans >= inf) {
            ans = -1;
        }
        std::cout << ans << "\n";
    }

    return 0;
}
