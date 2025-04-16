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
    constexpr ModBase() : x{} {}
    template <class T> constexpr ModBase(T x) : x{norm(x % mod())} {}
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

constexpr u32 P = 998244353;
using Z = Mod32<P>;

template <int V> constexpr Z inv = Z(V).inv();

struct Comb {
    int n;
    std::vector<Z> _fac, _invfac, _inv;
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() {
        init(n);
    }
    void init(int m) {
        if (m <= n) {
            return;
        }
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }
    Z fac(int m) {
        if (m > n) {
            init(2 * m);
        }
        return _fac[m];
    }
    Z invfac(int m) {
        if (m > n) {
            init(2 * m);
        }
        return _invfac[m];
    }
    Z inv(int m) {
        if (m > n) {
            init(2 * m);
        }
        return _inv[m];
    }
    Z binom(int n, int m) {
        if (n < m || m < 0) {
            return 0;
        } else {
            return fac(n) * invfac(m) * invfac(n - m);
        }
    }
} comb;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    std::vector<int> c(n);
    for (auto a : a) {
        c[a]++;
    }

    std::vector<Z> pw(n + 1);
    pw[0] = 1;
    for (int i = 0; i < n; i++) {
        pw[i + 1] = 2 * pw[i];
    }

    Z ans = 0;
    std::vector<Z> dp(c[0] + 1);
    for (int i = 0; i <= c[0]; i++) {
        dp[i] = comb.binom(c[0], i);
        ans += dp[i] * i * pw[n - c[0]];
    }

    int t = c[0];
    for (int x = 1; x < n; x++) {
        t += c[x];
        for (int i = c[x - 1]; i > 0; i--) {
            dp[i - 1] += dp[i];
        }
        std::vector<Z> sum(c[x] + 1);
        sum[c[x]] = 1;
        for (int i = c[x]; i > 0; i--) {
            sum[i - 1] = sum[i] + comb.binom(c[x], i - 1);
        }
        std::vector<Z> ndp(c[x] + 1);
        for (int i = 0; i <= c[x]; i++) {
            if (i + 1 <= c[x - 1]) {
                ndp[i] += comb.binom(c[x], i) * dp[i + 1];
            }
            if (i <= c[x - 1]) {
                Z v = dp[i];
                if (i + 1 <= c[x - 1]) {
                    v -= dp[i + 1];
                }
                ndp[i] += sum[i] * v;
            }
            ans += ndp[i] * i * pw[n - t];
        }
        dp = std::move(ndp);
    }

    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
