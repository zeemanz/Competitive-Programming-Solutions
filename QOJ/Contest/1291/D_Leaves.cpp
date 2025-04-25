#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

std::vector<int> operator+(const std::vector<int> &lhs, const std::vector<int> &rhs) {
    std::vector<int> res = lhs;
    res.insert(res.end(), rhs.begin(), rhs.end());
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> l(n, -1), r(n, -1), a(n);
    for (int i = 0; i < n; i++) {
        int t;
        std::cin >> t;

        if (t == 1) {
            std::cin >> l[i] >> r[i];
            l[i]--;
            r[i]--;
        } else {
            std::cin >> a[i];
        }
    }

    auto dfs = [&](auto &&self, int u) -> std::vector<std::vector<int>> {
        if (u == -1) {
            return {{}};
        }
        if (l[u] == -1 && r[u] == -1) {
            return {{a[u]}};
        }
        auto lhs = self(self, l[u]);
        auto rhs = self(self, r[u]);
        std::vector<std::vector<int>> res(std::min(int(lhs.size() + rhs.size()), m + 1));
        for (int i = 0; i < lhs.size(); i++) {
            for (int j = 0; j < rhs.size() && i + j < res.size(); j++) {
                auto x = lhs[i];
                auto y = rhs[j];
                if (res[i + j].empty()) {
                    res[i + j] = x + y;
                } else {
                    res[i + j] = std::min(res[i + j], x + y);
                }
                if (i + j + 1 < res.size()) {
                    if (res[i + j + 1].empty()) {
                        res[i + j + 1] = y + x;
                    } else {
                        res[i + j + 1] = std::min(res[i + j + 1], y + x);
                    }
                }
            }
        }
        return res;
    };
    auto res = dfs(dfs, 0);

    auto ans = res[m];
    for (int i = m - 2; i >= 0; i -= 2) {
        ans = std::min(ans, res[i]);
    }
    for (int i = 0; i < ans.size(); i++) {
        std::cout << ans[i] << " \n"[i == ans.size() - 1];
    }

    return 0;
}
