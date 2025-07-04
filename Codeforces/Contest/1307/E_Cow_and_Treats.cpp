#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using u128 = unsigned __int128;

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
    return static_cast<u64>(a) * b % P;
}

template <u64 P> constexpr u64 mulMod(u64 a, u64 b) {
    return static_cast<u128>(a) * b % P;
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

template <int V> constexpr Z CInv = Z(V).inv();

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
    Z catalan(int n) {
        return binom(2 * n, n) - binom(2 * n, n - 1);
    }
} comb;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> s(n);
    for (auto &s : s) {
        std::cin >> s;
        s--;
    }

    std::vector<std::vector<int>> cow(n);
    for (int i = 0; i < m; i++) {
        int f, h;
        std::cin >> f >> h;
        f--;

        cow[f].push_back(h);
    }
    for (int i = 0; i < n; i++) {
        std::sort(cow[i].begin(), cow[i].end());
    }

    std::vector pre(n + 1, std::vector(n, 0));
    std::vector suf(n + 1, std::vector(n, 0));
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i];
        pre[i + 1][s[i]]++;
    }
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = suf[i + 1];
        suf[i][s[i]]++;
    }

    Z ans = 1;
    int max = 0;
    for (int j = 0; j < n; j++) {
        int x = std::upper_bound(cow[j].begin(), cow[j].end(), suf[0][j]) - cow[j].begin();
        if (x > 0) {
            ans *= x;
            max++;
        }
    }
    for (int i = 1; i <= n; i++) {
        auto it = std::find(cow[s[i - 1]].begin(), cow[s[i - 1]].end(), pre[i][s[i - 1]]);
        if (it == cow[s[i - 1]].end()) {
            continue;
        }
        Z cur = 1;
        int sum = 1;
        for (int j = 0; j < n; j++) {
            if (j == s[i - 1]) {
                int x = std::upper_bound(cow[j].begin(), cow[j].end(), suf[i][j]) - cow[j].begin();
                if (suf[i][j] >= pre[i][j]) {
                    x--;
                }
                if (x > 0) {
                    cur *= x;
                    sum++;
                }
            } else {
                int x = std::upper_bound(cow[j].begin(), cow[j].end(), pre[i][j]) - cow[j].begin();
                int y = std::upper_bound(cow[j].begin(), cow[j].end(), suf[i][j]) - cow[j].begin();
                int a = std::min(x, y), b = std::max(x, y);
                if (b == 0) {
                    continue;
                }
                if (a == 0) {
                    cur *= b;
                    sum++;
                } else if (a == 1 && b == 1) {
                    cur *= 2;
                    sum++;
                } else {
                    cur *= 2 * comb.binom(a, 2) + a * (b - a);
                    sum += 2;
                }
            }
        }
        if (sum > max) {
            ans = cur;
            max = sum;
        } else if (sum == max) {
            ans += cur;
        }
    }

    std::cout << max << " " << ans << "\n";

    return 0;
}
