#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr int inf = 1E9;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<int> s(n);
        for (auto &s : s) {
            std::cin >> s;
        }

        std::map<std::pair<int, int>, int> dp;
        dp[{inf, inf}] = 0;

        for (auto s : s) {
            std::map<std::pair<int, int>, int> ndp;
            for (auto [k, v] : dp) {
                auto [a, b] = k;
                int na = std::min(a, s);
                int nb = std::min(b, s);
                if (!ndp.contains({na, b})) {
                    ndp[{na, b}] = v + s - na;
                } else {
                    ndp[{na, b}] = std::min(ndp[{na, b}], v + s - na);
                }
                if (!ndp.contains({a, nb})) {
                    ndp[{a, nb}] = v + s - nb;
                } else {
                    ndp[{a, nb}] = std::min(ndp[{a, nb}], v + s - nb);
                }
            }
            dp = std::move(ndp);
        }

        int ans = inf;
        for (auto [k, v] : dp) {
            ans = std::min(ans, v);
        }
        std::cout << ans << "\n";
    }

    return 0;
}
