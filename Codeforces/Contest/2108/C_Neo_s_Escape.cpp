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

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        auto v = a;
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
        for (auto &a : a) {
            a = std::lower_bound(v.begin(), v.end(), a) - v.begin();
        }

        std::vector<std::vector<std::pair<int, int>>> pos(v.size());
        for (int i = 0; i < n; i++) {
            if (pos[a[i]].empty()) {
                pos[a[i]].emplace_back(i, i + 1);
            } else {
                if (pos[a[i]].back().second == i) {
                    pos[a[i]].back().second = i + 1;
                } else {
                    pos[a[i]].emplace_back(i, i + 1);
                }
            }
        }

        int ans = 0;
        std::set<std::pair<int, int>> seg;
        for (int x = v.size() - 1; x >= 0; x--) {
            for (auto [l, r] : pos[x]) {
                auto lit = seg.upper_bound({l, r});
                auto rit = seg.upper_bound({l, r});
                if (lit != seg.begin() && rit != seg.end()) {
                    lit = std::prev(lit);
                    auto [ll, lr] = *lit;
                    auto [rl, rr] = *rit;
                    if (lr == l && rl == r) {
                        seg.erase(lit);
                        seg.erase(rit);
                        seg.emplace(ll, rr);
                    } else if (lr == l) {
                        seg.erase(lit);
                        seg.emplace(ll, r);
                    } else if (rl == r) {
                        seg.erase(rit);
                        seg.emplace(l, rr);
                    } else {
                        ans++;
                        seg.emplace(l, r);
                    }
                } else if (lit != seg.begin()) {
                    lit = std::prev(lit);
                    auto [ll, lr] = *lit;
                    if (lr == l) {
                        seg.erase(lit);
                        seg.emplace(ll, r);
                    } else {
                        ans++;
                        seg.emplace(l, r);
                    }
                } else if (rit != seg.end()) {
                    auto [rl, rr] = *rit;
                    if (rl == r) {
                        seg.erase(rit);
                        seg.emplace(l, rr);
                    } else {
                        ans++;
                        seg.emplace(l, r);
                    }
                } else {
                    ans++;
                    seg.emplace(l, r);
                }
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
