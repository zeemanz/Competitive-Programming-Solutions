#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        std::cin >> a[i] >> b[i];
        a[i]--;
        b[i]--;

        if (a[i] > 0) {
            if (b[i] + a[i] < n) {
                b[i] += a[i];
                a[i] = 0;
            } else {
                a[i] -= n - b[i];
                b[i] = 0;
                std::swap(a[i], b[i]);
            }
        }
    }

    std::vector<int> c(n);
    for (int i = 0; i < m; i++) {
        assert(a[i] == 0);
        c[b[i]]++;
    }

    i64 pre = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        ans += pre * c[i];
        pre += c[i];
    }

    std::cout << ans << "\n";

    return 0;
}
