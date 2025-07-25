#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    auto work = [&](int x) {
        std::vector<int> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = s[i] - '0';
        }
        std::vector<int> f(n);
        for (int i = 0; i < n; i++, x ^= 1) {
            f[i] = a[i] ^ x;
        }
        if (std::count(f.begin(), f.end(), 1) == n) {
            return n / 2;
        }
        int i = 0;
        while (f[i]) {
            i = (i + 1) % n;
        }
        int res = 0;
        std::vector<int> v(n);
        for (int j = i; !v[i]; i = j) {
            if (f[i]) {
                int c = 0;
                while (f[j]) {
                    c++;
                    v[j] = 1;
                    j = (j + 1) % n;
                }
                res += (c + 1) / 2;
            } else {
                v[j] = 1;
                j = (j + 1) % n;
            }
            i = j;
        }
        return res;
    };

    int ans = std::min(work(0), work(1));
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
