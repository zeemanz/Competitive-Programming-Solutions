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

        if (k == 1) {
            if (n == 1) {
                std::cout << "YES\n";
                std::cout << "1\n";
            } else {
                std::cout << "NO\n";
            }
            continue;
        }

        if (k % 2 && n % 2 == 0) {
            std::cout << "NO\n";
            continue;
        }

        std::vector<int> a(n);
        std::iota(a.begin(), a.end(), 0);

        std::set<std::vector<int>> s, p;
        if (k % 2) {
            std::vector<int> b(n);
            b[0] = n / 2;
            for (int i = 1; i < n; i++) {
                b[i] = (b[i - 1] + 1) % n;
            }
            std::vector<int> c(n);
            for (int i = 0; i < n; i++) {
                c[i] = (n / 2) * 3 - a[i] - b[i];
            }
            s.insert(a);
            s.insert(b);
            s.insert(c);
            p.insert(a);
            p.insert(b);
            p.insert(c);
        }
        do {
            if (p.size() == k) {
                break;
            }
            auto b = a;
            for (int i = 0; i < n; i++) {
                b[i] = n - b[i] - 1;
            }
            if (s.contains(a) || s.contains(b)) {
                continue;
            }
            if (p.contains(a) || p.contains(b)) {
                break;
            }
            p.insert(a);
            p.insert(b);
        } while (std::next_permutation(a.begin(), a.end()));

        if (p.size() == k) {
            std::cout << "YES\n";
            for (auto p : p) {
                for (int i = 0; i < n; i++) {
                    std::cout << p[i] + 1 << " \n"[i + 1 == n];
                }
            }
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
