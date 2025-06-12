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
        for (int i = 0; i < n; i++) {
            std::cin >> a[i] >> b[i];
            a[i]--;
        }

        std::vector<std::map<int, std::vector<int>>> id(n);
        for (int i = 0; i < n; i++) {
            id[a[i]][b[i]].push_back(i);
        }

        std::set<int> ans, cur;
        for (int a = n - 1; a >= 0; a--) {
            cur.clear();
            int sum = 0;
            for (auto [b, v] : id[a]) {
                sum += v.size();
            }
            int x = n, res = ans.size();
            for (auto it = id[a].begin(); it != id[a].end(); it++) {
                auto [b, v] = *it;
                if (std::min(int(ans.size()), b) + sum > res) {
                    x = b;
                    res = std::min(int(ans.size()), b) + sum;
                }
                sum -= v.size();
            }
            for (auto it = id[a].begin(); it != id[a].end(); it++) {
                auto [b, v] = *it;
                if (b >= x) {
                    while (ans.size() > b) {
                        ans.erase(*ans.begin());
                    }
                    cur.insert(v.begin(), v.end());
                }
            }
            ans.insert(cur.begin(), cur.end());
        }

        std::cout << ans.size() << "\n";
        for (auto i : ans) {
            std::cout << i + 1 << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
