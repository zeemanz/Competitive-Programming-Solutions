#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

template <class T> constexpr T power(T a, u64 n) {
    T res{1};
    for (; n != 0; n /= 2, a *= a) {
        if (n % 2 == 1) {
            res *= a;
        }
    }
    return res;
}

template <u32 P> constexpr u32 mulMod(u32 a, u32 b) {
    return 1ULL * a * b % P;
}

template <u64 P> constexpr u64 mulMod(u64 a, u64 b) {
    u64 res = a * b - u64(1.0L * a * b / P - 0.5L) * P;
    return res % P;
}

template <class U, U P> struct ModBase {
    U x;
    constexpr ModBase() : x{0} {}
    template <class T> constexpr ModBase(T x) : x{norm(x % T(mod()))} {}
    static constexpr U mod() {
        return P;
    }
    static constexpr U norm(U x) {
        if ((x >> (8 * sizeof(U) - 1) & 1) == 1) {
            x += mod();
        }
        if (x >= mod()) {
            x -= mod();
        }
        return x;
    }
    constexpr U val() const {
        return x;
    }
    constexpr ModBase operator-() const {
        return ModBase(mod() - x);
    }
    constexpr ModBase inv() const {
        return power(*this, mod() - 2);
    }
    constexpr ModBase &operator+=(const ModBase &rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr ModBase &operator-=(const ModBase &rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr ModBase &operator*=(const ModBase &rhs) & {
        x = mulMod<mod()>(x, rhs.x);
        return *this;
    }
    constexpr ModBase &operator/=(const ModBase &rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr ModBase operator+(ModBase lhs, const ModBase &rhs) {
        return lhs += rhs;
    }
    friend constexpr ModBase operator-(ModBase lhs, const ModBase &rhs) {
        return lhs -= rhs;
    }
    friend constexpr ModBase operator*(ModBase lhs, const ModBase &rhs) {
        return lhs *= rhs;
    }
    friend constexpr ModBase operator/(ModBase lhs, const ModBase &rhs) {
        return lhs /= rhs;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const ModBase &rhs) {
        return os << rhs.val();
    }
    friend constexpr bool operator==(const ModBase &lhs, const ModBase &rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(const ModBase &lhs, const ModBase &rhs) {
        return lhs.val() != rhs.val();
    }
    friend constexpr bool operator<(const ModBase &lhs, const ModBase &rhs) {
        return lhs.val() < rhs.val();
    }
};

template <u32 P> using Mod32 = ModBase<u32, P>;
template <u64 P> using Mod64 = ModBase<u64, P>;

constexpr u32 P = 1000000007;
using Z = Mod32<P>;

template <int V> constexpr Z inv = Z(V).inv();

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
                _prime.push_back(i);
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
};

template <class T> struct Min25 {
    inline static Sieve sieve = Sieve(100000);
    using Func = T (*)(int, int, i64);
    i64 n, sqrtn, cnt;
    std::vector<i64> num;
    std::vector<T> coef;
    std::vector<std::vector<T>> sum, ini, val;
    Min25() : n{0}, sqrtn{0} {}
    Min25(i64 n, const std::initializer_list<T> &coef, const std::initializer_list<Func> &func) {
        init(n, coef, func);
    }
    void init(i64 m, const std::initializer_list<T> &coef, const std::initializer_list<Func> &func) {
        n = m;
        sqrtn = std::sqrt(n);
        cnt = sieve.count(sqrtn);
        num.clear();
        for (i64 i = 1; i <= n; i = n / (n / i) + 1) {
            num.push_back(n / i);
        }
        this->coef = coef;
        sum.assign(func.size(), std::vector<T>(cnt + 1));
        ini.assign(func.size(), std::vector<T>(num.size()));
        for (int i = 0; auto f : func) {
            for (int j = 0; j < cnt; j++) {
                auto b = sieve.prime(j);
                sum[i][j + 1] = sum[i][j] + f(b, 1, b);
            }
            auto c = f(0, 0, 1);
            for (int j = 0; j < num.size(); j++) {
                ini[i][j] = f(0, 0, num[j]) - c;
            }
            i++;
        }
        for (int i = 0; auto f : func) {
            for (int j = 0; j < cnt; j++) {
                auto b = sieve.prime(j);
                for (int k = 0; k < num.size(); k++) {
                    if (1LL * b * b > num[k]) {
                        break;
                    }
                    ini[i][k] -= f(b, 1, b) * (ini[i][rank(num[k] / b)] - sum[i][j]);
                }
            }
            i++;
        }
        val.assign(cnt, {});
        for (int i = 0; i < cnt; i++) {
            auto b = sieve.prime(i);
            val[i].assign(int(std::ceil(std::log(n) / std::log(b))) + 1, 0);
            for (i64 e = 1, p = b, c = 0; p <= n; e++, p *= b, c = 1) {
                for (int j = 0; auto f : func) {
                    val[i][e] += this->coef[j++] * f(b, e, p);
                }
            }
        }
    }
    int rank(i64 m) {
        if (m <= sqrtn) {
            return num.size() - m;
        } else {
            return n / m - 1;
        }
    }
    T dfs(i64 m, int i) {
        if (sieve.prime(i) > m) {
            return 0;
        }
        T res = 0;
        for (int j = 0; j < coef.size(); j++) {
            res += coef[j] * (ini[j][rank(m)] - sum[j][i]);
        }
        for (; i < cnt; i++) {
            auto b = sieve.prime(i);
            if (1LL * b * b > m) {
                break;
            }
            for (i64 e = 1, p = b, c = 0; p <= m; e++, p *= b, c = 1) {
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

    auto f0 = [](int b, int e, i64 p) {
        if (b == 0) {
            return Z(p) * (p + 1) * (2 * p + 1) * inv<6>;
        } else {
            return Z(p) * p;
        }
    };
    auto f1 = [](int b, int e, i64 p) {
        if (b == 0) {
            return Z(p) * (p + 1) * inv<2>;
        } else {
            return Z(p);
        }
    };
    Min25<Z> min25(n, {1, -1}, {f0, f1});

    std::cout << min25(n) + 1 << "\n";

    return 0;
}
