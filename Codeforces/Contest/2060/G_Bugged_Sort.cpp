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

        std::vector<int> a(n), b(n);
        for (auto &a : a) {
            std::cin >> a;
        }
        for (auto &b : b) {
            std::cin >> b;
        }

        std::vector<int> ord(n);
        std::iota(ord.begin(), ord.end(), 0);
        std::ranges::sort(ord, [&](int i, int j) { return std::min(a[i], b[i]) < std::min(a[j], b[j]); });

        int dp[2][2]{{1, 0}, {1, 0}};
        for (int pa = 0, pb = 0; int i : ord) {
            int ndp[2][2]{};
            for (int j : {0, 1}) {
                if (j == 1) {
                    std::swap(pa, pb);
                }
                for (int k : {0, 1}) {
                    int ca = a[i], cb = b[i];
                    for (int nj : {0, 1}) {
                        if (nj == 1) {
                            std::swap(ca, cb);
                        }
                        if (ca > pa && cb > pb) {
                            ndp[nj][k ^ nj] |= dp[j][k];
                        }
                    }
                }
            }
            std::swap(dp, ndp);
            pa = a[i];
            pb = b[i];
        }

        if (dp[0][0] || dp[1][0]) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
