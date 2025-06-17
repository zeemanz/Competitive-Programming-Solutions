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
