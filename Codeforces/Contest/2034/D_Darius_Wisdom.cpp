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

        std::vector<std::set<int>> pos(3);
        for (int i = 0; i < n; i++) {
            pos[a[i]].insert(i);
        }

        std::vector<std::pair<int, int>> ans;
        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                if (!pos[0].empty()) {
                    int j = *pos[0].rbegin();
                    if (i < j) {
                        pos[0].erase(j);
                        pos[1].insert(j);
                        std::swap(a[i], a[j]);
                        ans.emplace_back(i, j);
                    }
                }
            } else if (a[i] == 2) {
                if (!pos[1].empty()) {
                    int j = *pos[1].rbegin();
                    if (i < j) {
                        pos[1].erase(j);
                        std::swap(a[i], a[j]);
                        ans.emplace_back(i, j);
                        i--;
                    }
                }
            }
        }

        std::cout << ans.size() << "\n";
        for (auto [i, j] : ans) {
            std::cout << i + 1 << " " << j + 1 << "\n";
        }
    }

    return 0;
}
