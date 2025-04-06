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

template <u32 P> constexpr u32 mulMod(u32 a, u32 b) { return 1ULL * a * b % P; }

template <u64 P> constexpr u64 mulMod(u64 a, u64 b) {
    u64 res = a * b - u64(1.0L * a * b / P - 0.5L) * P;
    return res % P;
}

template <class U, U P> struct ModBase {
    U x;
    constexpr ModBase() : x{0} {}
    template <class T> constexpr ModBase(T x) : x{norm(x % mod())} {}
    static constexpr U mod() { return P; }
    static constexpr U norm(U x) {
        if ((x >> (8 * sizeof(U) - 1) & 1) == 1) {
            x += mod();
        }
        if (x >= mod()) {
            x -= mod();
        }
        return x;
    }
    constexpr U val() const { return x; }
    constexpr ModBase operator-() const { return ModBase(mod() - x); }
    constexpr ModBase inv() const { return power(*this, mod() - 2); }
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
    constexpr ModBase &operator/=(const ModBase &rhs) & { return *this *= rhs.inv(); }
    friend constexpr ModBase operator+(ModBase lhs, const ModBase &rhs) { return lhs += rhs; }
    friend constexpr ModBase operator-(ModBase lhs, const ModBase &rhs) { return lhs -= rhs; }
    friend constexpr ModBase operator*(ModBase lhs, const ModBase &rhs) { return lhs *= rhs; }
    friend constexpr ModBase operator/(ModBase lhs, const ModBase &rhs) { return lhs /= rhs; }
    friend constexpr std::ostream &operator<<(std::ostream &os, const ModBase &rhs) { return os << rhs.val(); }
    friend constexpr bool operator==(const ModBase &lhs, const ModBase &rhs) { return lhs.val() == rhs.val(); }
    friend constexpr bool operator!=(const ModBase &lhs, const ModBase &rhs) { return lhs.val() != rhs.val(); }
    friend constexpr bool operator<(const ModBase &lhs, const ModBase &rhs) { return lhs.val() < rhs.val(); }
};

template <u32 P> using Mod32 = ModBase<u32, P>;
template <u64 P> using Mod64 = ModBase<u64, P>;

constexpr u32 P = 1000000007;
using Z = Mod32<P>;

template <int V> constexpr Z inv = Z(V).inv();

struct Comb {
    int n;
    std::vector<Z> _fac, _invfac, _inv;
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() { init(n); }
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

    int m = 0;
    std::vector<int> pos(n, -1);
    for (int i = 0; i < n; i++) {
        if (a[i] != -1) {
            pos[a[i]] = i;
        } else {
            m++;
        }
    }

    std::vector<int> sum(n + 1), cnt(n + 1);
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + (a[i] == -1);
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            cnt[sum[j] - sum[i]]++;
        }
    }

    Z ans = 0;
    int cur = 0, l = n, r = 0;
    for (int x = 0; x < n; x++) {
        if (pos[x] == -1) {
            cur++;
        } else {
            if (l > r) {
                l = pos[x];
                r = pos[x] + 1;
                cnt.assign(n + 1, 0);
                for (int i = 0; i <= l; i++) {
                    for (int j = r; j <= n; j++) {
                        cnt[sum[j] - sum[i]]++;
                    }
                }
            } else {
                while (l > pos[x]) {
                    for (int i = r; i <= n; i++) {
                        cnt[sum[i] - sum[l]]--;
                    }
                    l--;
                }
                while (r <= pos[x]) {
                    for (int i = 0; i <= l; i++) {
                        cnt[sum[r] - sum[i]]--;
                    }
                    r++;
                }
            }
        }
        for (int i = cur; i <= n; i++) {
            ans += cnt[i] * comb.binom(i, cur) * comb.fac(cur) * comb.fac(m - cur);
        }
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
