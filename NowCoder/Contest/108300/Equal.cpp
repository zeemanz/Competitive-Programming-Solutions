#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

std::vector<int> primes, minp;

void sieve(int n) {
    primes.clear();
    minp.assign(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (1LL * i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    sieve(5000000);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        if (n % 2) {
            std::cout << "YES\n";
        } else if (n == 2) {
            if (a[0] == a[1]) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        } else {
            std::map<int, int> s;
            for (auto a : a) {
                for (int p = minp[a]; a > 1; p = minp[a]) {
                    while (p == minp[a]) {
                        s[p] ^= 1;
                        a /= p;
                    }
                }
            }

            bool ok = true;
            for (auto [k, v] : s) {
                ok &= v == 0;
            }

            if (ok) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }
    }

    return 0;
}
