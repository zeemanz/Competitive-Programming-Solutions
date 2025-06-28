#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

u64 mul(u64 a, u64 b, u64 m) {
    return static_cast<u128>(a) * b % m;
}

u64 power(u64 a, u64 b, u64 m) {
    u64 res = 1;
    for (; b > 0; b /= 2, a = mul(a, a, m)) {
        if (b % 2 == 1) {
            res = mul(res, a, m);
        }
    }
    return res;
}

bool isPrime(i64 n) {
    if (n < 4) {
        return n == 2 || n == 3;
    }
    if (n % 2 == 0) {
        return false;
    }
    int s = std::countr_zero(u64(n - 1));
    i64 d = (n - 1) >> s;
    for (auto a : {2, 3, 5, 7, 11, 13, 17}) {
        if (a == n) {
            return true;
        }
        i64 x = power(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }
        for (int i = 1; i < s; i++) {
            x = mul(x, x, n);
            if (x == n - 1) {
                break;
            }
        }
        if (x != n - 1) {
            return false;
        }
    }
    return true;
}

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

    sieve(10000000);

    i64 l, r;
    std::cin >> l >> r;

    int ans = 1;
    for (auto p : primes) {
        if (p > r) {
            break;
        }
        i64 x = 1;
        while (x <= r) {
            if (x > l) {
                ans++;
            }
            if (i128(x) * p > r) {
                break;
            }
            x *= p;
        }
    }

    for (i64 i = l + 1; i <= r; i++) {
        if (isPrime(i)) {
            ans++;
        }
    }

    std::cout << ans << "\n";

    return 0;
}
