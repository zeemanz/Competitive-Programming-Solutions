#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr u64 m = 93824992236885ULL;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        std::vector<int> v(63);
        for (int i = 0; i < 62; i++) {
            u64 x = 0;
            for (int j = 0; j < 2; j++) {
                x |= 1ULL << (i + j);
            }
            std::cout << "? " << x << std::endl;
            std::cin >> v[i];
        }
        std::cout << "? " << m << std::endl;
        std::cin >> v[62];

        u64 cand[2][63]{};
        cand[1][0] = 1;
        cand[1][1] = 2;
        for (int i = 0; i < 61; i++) {
            if (v[i] == v[i + 1]) {
                for (int j = 0; j < 2; j++) {
                    cand[j][i + 2] = cand[j][i] | (u64(j) << (i + 2));
                }
            } else {
                for (int j = 0; j < 2; j++) {
                    cand[j][i + 2] = cand[j ^ 1][i] | (u64(j) << (i + 2));
                }
            }
        }

        auto check = [&](u64 n) {
            bool ok = true;
            for (int i = 0; i < 62; i++) {
                u64 x = 0;
                for (int j = 0; j < 2; j++) {
                    x |= 1ULL << (i + j);
                }
                ok &= std::popcount(n ^ x) == v[i];
            }
            return ok && std::popcount(n ^ m) == v[62];
        };

        u64 n;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                u64 m = cand[i][61] | cand[j][62];
                if (check(m)) {
                    n = m;
                    break;
                }
                m |= 1ULL << 63;
                if (check(m)) {
                    n = m;
                    break;
                }
            }
        }

        std::cout << "! " << n << std::endl;
    }

    return 0;
}
