#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n;
    i64 x, y, z;
    std::cin >> n >> x >> y >> z;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    std::vector<int> c(n + 1);
    for (auto a : a) {
        c[a]++;
    }

    int max = 1, sec = 1;
    for (int i = 1; i <= n; i++) {
        if (c[i] > max) {
            sec = max;
            max = c[i];
        } else if (c[i] > sec) {
            sec = c[i];
        }
    }

    std::vector<int> sum(n + 1), cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        sum[c[i]] += c[i];
        cnt[c[i]]++;
    }
    for (int i = n - 1; i >= 0; i--) {
        sum[i] += sum[i + 1];
        cnt[i] += cnt[i + 1];
    }

    i64 ans = 0;
    for (int i = 0; i < sec; i++) {
        int k = n - i - sum[i + 1] + 1LL * cnt[i + 1] * (i + 1);
        ans = std::max(ans, k * x + (n - k - i) * y + i * z);
    }

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
