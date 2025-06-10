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
            a--;
        }

        std::set<int> s;
        std::vector<std::vector<int>> pos(n);
        for (int i = 0; i < n; i++) {
            pos[a[i]].push_back(i);
            s.insert(a[i]);
        }

        int ans = 0, r = n;
        while (!s.empty()) {
            for (auto x : s) {
                while (!pos[x].empty() && pos[x].back() >= r) {
                    pos[x].pop_back();
                }
            }
            bool f = false;
            for (auto x : s) {
                if (!pos[x].empty()) {
                    f = true;
                    r = std::min(r, pos[x].back());
                }
            }
            for (auto it = s.begin(); it != s.end();) {
                if (pos[*it].empty()) {
                    it = s.erase(it);
                } else {
                    it++;
                }
            }
            ans += f;
        }

        std::cout << ans << "\n";
    }

    return 0;
}
