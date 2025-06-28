#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, M, D;
    std::cin >> n >> M >> D;

    std::vector<int> sum(M * D + 1);
    for (int i = 0; i < n; i++) {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        a--;
        b--;
        c--;
        d--;

        sum[a * D + b]++;
        sum[c * D + d + 1]--;
    }

    for (int i = 1; i <= M * D; i++) {
        sum[i] += sum[i - 1];
    }

    for (int i = 0; i < M * D; i++) {
        if (sum[i] == 0) {
            int x = i / D;
            int y = i % D;
            std::cout << x + 1 << " " << y + 1 << "\n";
            return 0;
        }
    }

    std::cout << "Online\n";

    return 0;
}
