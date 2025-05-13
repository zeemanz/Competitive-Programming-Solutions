#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

struct Sieve {
    int n;
    std::vector<int> _prime, _lpf;
    Sieve() : n{2}, _prime{2}, _lpf{0, 0, 2} {}
    Sieve(int n) : Sieve() {
        init(n);
    }
    void init(int m) {
        if (m <= n) {
            return;
        }
        n = m;
        _lpf.resize(n + 1);
        for (int i = 2; i <= n; i++) {
            if (_lpf[i] == 0) {
                _prime.emplace_back(i);
                _lpf[i] = i;
            }
            for (auto p : _prime) {
                if (1LL * i * p > n) {
                    break;
                }
                _lpf[i * p] = p;
                if (p == _lpf[i]) {
                    break;
                }
            }
        }
    }
    int prime(int i) {
        while (i >= _prime.size()) {
            init(2 * n);
        }
        return _prime[i];
    }
    int lpf(int m) {
        if (m > n) {
            init(2 * m);
        }
        return _lpf[m];
    }
    int size() {
        return _prime.size();
    }
    int count(int m) {
        while (_prime.back() <= m) {
            init(2 * n);
        }
        return std::upper_bound(_prime.begin(), _prime.end(), m) - _prime.begin();
    }
} sieve(500000);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::multiset<int>> s(500001);

    while (n--) {
        std::string o;
        std::cin >> o;

        if (o == "+") {
            int v, w;
            std::cin >> v >> w;

            while (v > 1) {
                int p = sieve.lpf(v);
                while (p == sieve.lpf(v)) {
                    v /= p;
                }
                s[p].insert(w);
            }
        } else if (o == "-") {
            int v, w;
            std::cin >> v >> w;

            while (v > 1) {
                int p = sieve.lpf(v);
                while (p == sieve.lpf(v)) {
                    v /= p;
                }
                s[p].extract(w);
            }
        } else {
            int k;
            std::cin >> k;

            int ans = 0;
            while (k > 1) {
                int p = sieve.lpf(k);
                while (p == sieve.lpf(k)) {
                    k /= p;
                }
                if (!s[p].empty()) {
                    ans = std::max(ans, *s[p].rbegin());
                }
            }

            std::cout << ans << "\n";
        }
    }

    return 0;
}
