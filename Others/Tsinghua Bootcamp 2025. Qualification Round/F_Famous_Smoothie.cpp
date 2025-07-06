#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    std::sort(a.begin(), a.end(), std::greater());
    std::sort(a.begin() + 1, a.end());

    int x = 0;
    std::set<int> s;

    std::vector<int> b(n);
    for (int i = 0; i < n; i++) {
        s.insert(a[i]);
        while (s.contains(x)) {
            x++;
        }
        b[i] = x;
    }
    std::set<int> t(b.begin(), b.end());

    int ans = 0;
    while (t.contains(ans)) {
        ans++;
    }

    std::cout << ans << "\n";

    return 0;
}
