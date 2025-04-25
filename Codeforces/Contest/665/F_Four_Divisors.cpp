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
} sieve(100000);

template <class T> struct Min25 {
    using Func = T (*)(int, int, i64);
    int pcnt;
    i64 n, sqrt;
    std::vector<i64> nums;
    std::vector<T> coef;
    std::vector<std::vector<T>> sum, ini, val;
    Min25() : n{0}, sqrt{0} {}
    Min25(i64 n, const std::vector<T> &coef, const std::vector<Func> &func, int lim = std::numeric_limits<u32>::max()) {
        init(n, coef, func, lim);
    }
    void init(i64 m, const std::vector<T> &coef, const std::vector<Func> &func,
              int lim = std::numeric_limits<u32>::max()) {
        n = m;
        sqrt = std::sqrt(n);
        pcnt = sieve.count(sqrt);
        nums.clear();
        for (i64 i = 1; i <= n; i = n / (n / i) + 1) {
            nums.emplace_back(n / i);
        }
        nums.emplace_back(0);
        std::reverse(nums.begin(), nums.end());
        sum.assign(func.size(), std::vector<T>(pcnt + 1));
        ini.assign(func.size(), std::vector<T>(nums.size()));
        for (int i = 0; i < func.size(); i++) {
            auto f = func[i];
            for (int j = 0; j < pcnt; j++) {
                auto b = sieve.prime(j);
                sum[i][j + 1] = sum[i][j] + f(b, 1, b);
            }
            auto c = f(0, 0, 1);
            for (int j = 1; j < nums.size(); j++) {
                ini[i][j] = f(0, 0, nums[j]) - c;
            }
        }
        for (int i = 0; i < func.size(); i++) {
            auto f = func[i];
            for (int j = 0; j < pcnt; j++) {
                auto b = sieve.prime(j);
                for (int k = nums.size() - 1; k > 0; k--) {
                    if (1LL * b * b > nums[k]) {
                        break;
                    }
                    ini[i][k] -= f(b, 1, b) * (ini[i][rank(nums[k] / b)] - sum[i][j]);
                }
            }
        }
        val.assign(pcnt, {});
        for (int i = 0; i < pcnt; i++) {
            auto b = sieve.prime(i);
            val[i].reserve(int(std::floor(std::log(n) / std::log(b))) + 1);
            val[i].emplace_back(0);
            for (i64 e = 1, p = b, c = 0; e <= lim && p <= n; e++, p *= b, c = 1) {
                val[i].emplace_back(0);
                for (int j = 0; j < coef.size(); j++) {
                    val[i][e] += coef[j] * func[j](b, e, p);
                }
            }
        }
        this->coef = coef;
    }
    int rank(i64 m) {
        if (m <= sqrt) {
            return m;
        } else {
            return nums.size() - n / m;
        }
    }
    T operator[](i64 m) {
        T res = 0;
        for (int i = 0; i < coef.size(); i++) {
            res += coef[i] * ini[i][rank(m)];
        }
        return res;
    }
    T dfs(i64 m, int i) {
        if (sieve.prime(i) > m) {
            return 0;
        }
        T res = 0;
        for (int j = 0; j < coef.size(); j++) {
            res += coef[j] * (ini[j][rank(m)] - sum[j][i]);
        }
        for (; i < pcnt; i++) {
            auto b = sieve.prime(i);
            if (1LL * b * b > m) {
                break;
            }
            for (i64 e = 1, p = b, c = 0; e < val[i].size() && p <= m; e++, p *= b, c = 1) {
                res += val[i][e] * (dfs(m / p, i + 1) + c);
            }
        }
        return res;
    }
    T operator()(i64 m) {
        return dfs(m, 0);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 n;
    std::cin >> n;

    auto f = [](int b, int e, i64 p) {
        if (b == 0) {
            return p;
        } else {
            return e == 1 ? 1LL : 0LL;
        }
    };
    Min25<i64> min25(n, {1}, {f}, 1);

    i64 ans = 0;
    for (i64 l = 1, r, p = 0; l <= n; l = r + 1) {
        r = n / (n / l);
        ans += (min25[r] - min25[l - 1]) * min25[n / l];
    }
    ans -= sieve.count(std::sqrt(n));
    ans /= 2;

    std::cout << ans + sieve.count(std::cbrt(n)) << "\n";

    return 0;
}
