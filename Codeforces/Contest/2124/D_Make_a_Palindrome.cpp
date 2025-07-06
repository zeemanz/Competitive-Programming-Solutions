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

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
            a--;
        }

        std::vector<std::vector<int>> p(n);
        for (int i = 0; i < n; i++) {
            p[a[i]].push_back(i);
        }

        int s = 0, x = 0;
        std::vector<int> v(n);
        while (x < n) {
            if (s + p[x].size() < k) {
                for (auto j : p[x]) {
                    v[j] = 1;
                }
            } else {
                break;
            }
            s += p[x].size();
            x++;
        }

        std::vector<int> b;
        for (int i = 0; i < n; i++) {
            if (v[i] || a[i] == x) {
                b.push_back(i);
            }
        }

        int l = 0, r = int(b.size()) - 1;
        std::vector<int> c;
        while (l < r) {
            int i = b[l], j = b[r];
            if (a[i] == a[j]) {
                c.push_back(i);
                c.push_back(j);
                l++;
                r--;
            } else {
                if (a[i] == x) {
                    l++;
                } else if (a[j] == x) {
                    r--;
                } else {
                    break;
                }
            }
        }
        if (l == r) {
            c.push_back(b[l]);
        }
        for (auto i : c) {
            v[i] = 0;
        }

        if (std::find(v.begin(), v.end(), 1) != v.end()) {
            std::cout << "NO\n";
        } else {
            if (c.size() >= k - 1) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }
    }

    return 0;
}
