#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    int n;
    std::cin >> n;

    std::vector<u64> w(n);
    for (auto &w : w) {
        w = rng();
    }

    std::vector<std::pair<int, int>> a;
    std::vector<std::pair<int, u64>> q;
    for (int i = 0; i < n; i++) {
        int l, r;
        std::cin >> l >> r;

        a.emplace_back(l, r);
        q.emplace_back(l, w[i]);
        q.emplace_back(r, 0);
        q.emplace_back(r + 1, w[i]);
    }
    std::sort(q.begin(), q.end());

    int p = -1;
    u64 s = 0;
    std::vector<u64> ans;
    for (auto [i, x] : q) {
        if (i != p) {
            ans.push_back(s);
        }
        p = i;
        s ^= x;
    }
    ans.push_back(s);

    std::sort(ans.begin(), ans.end());
    ans.erase(std::unique(ans.begin(), ans.end()), ans.end());
    std::cout << ans.size() << "\n";
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
