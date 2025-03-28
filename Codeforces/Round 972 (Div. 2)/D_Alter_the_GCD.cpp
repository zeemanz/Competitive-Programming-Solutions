#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a[2];
    for (int t : {0, 1}) {
        a[t].resize(n);
        for (auto &a : a[t]) {
            std::cin >> a;
        }
    }

    std::vector<int> pre[2];
    for (int t : {0, 1}) {
        pre[t].assign(n + 1, 0);
        for (int i = 0; i < n; i++) {
            pre[t][i + 1] = std::gcd(pre[t][i], a[t][i]);
        }
    }

    int suf[2]{};
    std::map<int, i64> ans;
    std::map<std::array<int, 2>, int> dp;
    for (int l = n - 1; l >= 0; l--) {
        std::map<std::array<int, 2>, int> ndp;
        for (auto [k, v] : dp) {
            auto nk = k;
            for (int t : {0, 1}) {
                nk[t] = std::gcd(nk[t], a[t][l]);
            }
            ndp[nk] += v;
        }
        ndp[{std::gcd(suf[1], a[0][l]), std::gcd(suf[0], a[1][l])}]++;
        dp = std::move(ndp);
        for (auto [k, v] : dp) {
            int x = 0;
            for (int t : {0, 1}) {
                x += std::gcd(k[t], pre[t ^ 1][l]);
            }
            ans[x] += v;
        }
        for (int t : {0, 1}) {
            suf[t] = std::gcd(suf[t], a[t][l]);
        }
    }

    auto [k, v] = *ans.rbegin();
    std::cout << k << " " << v << "\n";
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
