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
            a--;
        }
        for (auto &b : b) {
            std::cin >> b;
            b--;
        }

        std::vector<int> pa(n), pb(n);
        for (int i = 0; i < n; i++) {
            pa[a[i]] = i;
            pb[b[i]] = i;
        }

        bool ok = true;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            ok &= a[i] == b[pa[b[i]]];
            cnt += a[i] == b[i];
        }

        if (ok && cnt <= 1) {
            std::vector<std::pair<int, int>> ans;
            if (cnt == 1) {
                for (int i = 0; i < n; i++) {
                    if (a[i] == b[i]) {
                        int j = n / 2;
                        if (i != j) {
                            ans.emplace_back(i, j);
                            std::swap(pa[a[i]], pa[a[j]]);
                            std::swap(pb[b[i]], pb[b[j]]);
                            std::swap(a[i], a[j]);
                            std::swap(b[i], b[j]);
                        }
                        break;
                    }
                }
            }
            for (int i = 0; i < n - i - 1; i++) {
                int p = pa[b[i]];
                if (p == n - i - 1) {
                    continue;
                }
                ans.emplace_back(p, n - i - 1);
                std::swap(pa[a[p]], pa[a[n - i - 1]]);
                std::swap(pb[b[p]], pb[b[n - i - 1]]);
                std::swap(a[p], a[n - i - 1]);
                std::swap(b[p], b[n - i - 1]);
            }
            std::cout << ans.size() << "\n";
            for (auto [i, j] : ans) {
                std::cout << i + 1 << " " << j + 1 << "\n";
            }
        } else {
            std::cout << "-1\n";
        }
    }

    return 0;
}
