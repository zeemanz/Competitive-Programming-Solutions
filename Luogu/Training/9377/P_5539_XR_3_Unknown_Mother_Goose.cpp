#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, s;
    std::cin >> n >> s;

    std::vector<int> a(s);
    for (auto &a : a) {
        std::cin >> a;
    }

    std::vector<u64> f(n / 64 + 1);
    for (auto a : a) {
        if (a >= 64) {
            for (int i = 0; i <= n; i += a) {
                f[i / 64] |= 1ULL << (i % 64);
            }
        } else {
            std::vector<u64> g(a);
            for (int i = 0; i < 64 * a; i += a) {
                g[i / 64] |= 1ULL << (i % 64);
            }
            for (int i = 0; i < f.size(); i += a) {
                for (int j = 0; j < a && i + j < f.size(); j++) {
                    f[i + j] |= g[j];
                }
            }
        }
    }

    f[0] ^= 1ULL;
    for (int i = n + 1; i / 64 < f.size(); i++) {
        if (f[i / 64] >> (i % 64) & 1) {
            f[i / 64] ^= 1ULL << (i % 64);
        }
    }

    int ans = 0;
    for (int i = 0; i < f.size(); i++) {
        ans += std::popcount(f[i] & (f[i] << 1) & (f[i] << 2));
        if (i > 0) {
            ans += std::popcount((f[i] >> 1) & f[i] & (f[i - 1] >> 63));
            ans += std::popcount(f[i] & (f[i - 1] >> 63) & (f[i - 1] >> 62));
        }
    }
    std::cout << ans << "\n";

    return 0;
}
