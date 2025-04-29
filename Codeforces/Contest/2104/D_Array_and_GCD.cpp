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
} sieve(400000);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        std::vector<i64> sum(n + 1);
        for (int i = 0; i < n; i++) {
            sum[i + 1] = sum[i] + sieve.prime(i);
        }

        i64 tot = std::accumulate(a.begin(), a.end(), 0LL);
        if (sum[n] <= tot) {
            std::cout << "0\n";
            continue;
        }

        std::sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) {
            tot -= a[i];
            sum.pop_back();
            if (sum.back() <= tot) {
                std::cout << i + 1 << "\n";
                break;
            }
        }
    }

    return 0;
}
