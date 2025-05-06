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

        std::map<int, int, std::greater<>> p;
        for (int i = 0; i < n; i++) {
            p[a[i] + i + 1]++;
        }

        int pre = -1, tot = 0;
        std::vector<int> b;
        for (auto [cur, cnt] : p) {
            while (pre > cur && tot > 0) {
                b.push_back(pre);
                pre--;
                tot--;
            }
            pre = cur;
            tot += cnt;
        }
        while (tot--) {
            b.push_back(pre);
            pre--;
        }

        std::sort(b.begin(), b.end(), std::greater());
        b.erase(std::unique(b.begin(), b.end()), b.end());
        for (auto b : b) {
            std::cout << b << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
