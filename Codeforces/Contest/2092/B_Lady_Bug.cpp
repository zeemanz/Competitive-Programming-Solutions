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
        int n;
        std::cin >> n;

        std::string a, b;
        std::cin >> a >> b;

        int A[2][2]{}, B[2][2]{};
        for (int i = 0; i < n; i++) {
            A[a[i] - '0'][i % 2]++;
            B[b[i] - '0'][i % 2]++;
        }

        bool ok = true;
        for (int i = 0; i < 2; i++) {
            if (B[0][i] < A[1][i ^ 1]) {
                ok = false;
            }
        }

        std::cout << (ok ? "YES" : "NO") << "\n";
    }

    return 0;
}
