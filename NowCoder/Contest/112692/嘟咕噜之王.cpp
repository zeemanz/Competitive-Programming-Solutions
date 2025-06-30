#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = double;

constexpr f64 inf = 4E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n + 1);
    for (auto &a : a) {
        std::cin >> a;
    }

    std::vector<f64> e(n + 1, inf);
    e[n] = 0;

    for (int i = n - 1; i >= 0; i--) {
        f64 sum = 0;
        for (int j = i + 1; j <= n; j++) {
            sum += e[j];
            e[i] = std::min(e[i], (sum + 1LL * (j - i + 1) * a[j]) / (j - i));
        }
    }

    std::cout << std::fixed << std::setprecision(10) << e[0] << "\n";

    return 0;
}
