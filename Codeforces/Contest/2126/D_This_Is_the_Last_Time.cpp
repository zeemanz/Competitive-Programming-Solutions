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
        int n, k;
        std::cin >> n >> k;

        std::vector<int> l(n), r(n), real(n);
        for (int i = 0; i < n; i++) {
            std::cin >> l[i] >> r[i] >> real[i];
        }

        std::vector<int> ord(n);
        std::iota(ord.begin(), ord.end(), 0);
        std::sort(ord.begin(), ord.end(), [&](int i, int j) { return real[i] < real[j]; });

        std::set<int> s = {k};
        for (int i : ord) {
            auto it = s.lower_bound(l[i]);
            if (it != s.end() && *it <= r[i]) {
                s.insert(real[i]);
            }
        }

        std::cout << *s.rbegin() << "\n";
    }

    return 0;
}
