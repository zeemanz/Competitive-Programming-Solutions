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

        std::vector<int> b;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (a[i] > a[j]) {
                    b.push_back(a[i]);
                    b.push_back(a[j]);
                    break;
                }
            }
            if (!b.empty()) {
                break;
            }
        }

        if (b.empty()) {
            std::cout << "NO\n";
        } else {
            std::cout << "YES\n";
            std::cout << b.size() << "\n";
            for (int i = 0; i < b.size(); i++) {
                std::cout << b[i] << " \n"[i + 1 == b.size()];
            }
        }
    }

    return 0;
}
