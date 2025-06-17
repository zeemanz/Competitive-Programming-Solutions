#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

u64 mul(u64 a, u64 b, u64 m) {
    u64 res = a * b - u64(1.0L * a * b / m - 0.5L) * m;
    return res % m;
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

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

i64 factor(i64 n) {
    if (n % 2 == 0) {
        return 2;
    }
    if (isPrime(n)) {
        return n;
    }
    i64 m = 2;
    while (true) {
        i64 c = (rng() % (n - 1)) + 1;
        auto f = [&](i64 x) { return (mul(x, x, n) + c) % n; };
        i64 d = 1, x = m, y = m, p = 1, q = 0, v = 1;
        while (d == 1) {
            y = f(y);
            q++;
            v = mul(v, std::abs(x - y), n);
            if (q % 127 == 0) {
                d = std::gcd(v, n);
                v = 1;
            }
            if (p == q) {
                x = y;
                p *= 2;
                q = 0;
                d = std::gcd(v, n);
                v = 1;
            }
        }
        if (d != n) {
            return d;
        }
        m++;
    }
}

std::vector<i64> factorize(i64 n) {
    std::vector<i64> p;
    auto dfs = [&](auto &&self, i64 n) -> void {
        if (isPrime(n)) {
            p.push_back(n);
            return;
        }
        i64 d = factor(n);
        self(self, d);
        self(self, n / d);
    };
    dfs(dfs, n);
    std::sort(p.begin(), p.end());
    return p;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        i64 n;
        std::cin >> n;

        if (isPrime(n)) {
            std::cout << "Prime\n";
        } else {
            std::cout << factorize(n).back() << "\n";
        }
    }

    return 0;
}
