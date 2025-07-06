#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> d(n - 1);
    for (int i = 0; i < n - 1; i++) {
        std::cin >> d[i];
    }

    std::vector<int> sum(n);
    for (int i = 0; i < n - 1; i++) {
        sum[i + 1] = sum[i] + d[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            std::cout << sum[j] - sum[i] << " \n"[j + 1 == n];
        }
    }

    return 0;
}
