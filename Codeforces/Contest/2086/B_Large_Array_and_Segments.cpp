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
        i64 x;
        std::cin >> n >> k >> x;

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        i64 sum = std::accumulate(a.begin(), a.end(), 0LL);
        i64 t = x / sum;
        if (t * sum == x) {
            t--;
        }
        i64 c = t * n, v = t * sum;
        for (int i = n - 1; i >= 0; i--) {
            if (v + a[i] >= x) {
                break;
            }
            v += a[i];
            c++;
        }

        std::cout << std::max(1LL * n * k - c, 0LL) << "\n";
    }

    return 0;
}
