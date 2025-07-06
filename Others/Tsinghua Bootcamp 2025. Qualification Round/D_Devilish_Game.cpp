#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
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
    for (auto a : {2, 3, 5, 7, 11, 13, 17, 19, 23}) {
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int a, b, k;
        std::cin >> a >> b >> k;

        int p = a + b, q = a + b;
        while (p > b + 1 && !isPrime(p)) {
            p--;
        }
        while (!isPrime(q)) {
            q++;
        }

        if (isPrime(p) && a + b - p <= k) {
            std::cout << "Yes\n";
            continue;
        }

        if ((q - a - b) % (k + 1) != 0) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }

    return 0;
}
