#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }

    auto dot = [&](int i, int j, int k) {
        int x0 = x[j] - x[i], x1 = x[k] - x[j];
        int y0 = y[j] - y[i], y1 = y[k] - y[j];
        return 1LL * x0 * x1 + 1LL * y0 * y1;
    };

    std::vector<int> p{0, 1};
    for (int i = 2; i < n; i++) {
        int t = i;
        for (int j = i - 2; j >= 0; j--) {
            int a = p[j], &b = p[j + 1];
            int &c = j == i - 2 ? t : p[j + 2];
            if (dot(a, b, c) >= 0) {
                std::swap(b, c);
            } else {
                break;
            }
        }
        p.push_back(t);
    }

    for (int i = 0; i < n; i++) {
        std::cout << p[i] + 1 << " \n"[i == n - 1];
    }

    return 0;
}
