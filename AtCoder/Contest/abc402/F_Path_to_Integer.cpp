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

constexpr u32 mulMod(u32 a, u32 b, u32 P) {
    return 1ULL * a * b % P;
}

constexpr u64 mulMod(u64 a, u64 b, u64 P) {
    u64 res = a * b - u64(1.0L * a * b / P - 0.5L) * P;
    return res % P;
}

template <class U, U P> struct ModBase {
    inline static U M = 0;
    static constexpr void setMod(U M) {
        ModBase::M = M;
    }
    static constexpr U mod() {
        if (M == 0) {
            return P;
        } else {
            return M;
        }
    }
    U x;
    constexpr ModBase() : x{0} {}
    template <class T> constexpr ModBase(T x) : x{norm(x % mod())} {}
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
        x = mulMod(x, rhs.x, mod());
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    Z::setMod(m);

    std::vector a(n, std::vector(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
        }
    }

    std::vector<std::set<int>> p(n);
    auto pref = [&](auto &&self, int i, int j, Z v) -> void {
        if (i + j == n - 1) {
            p[i].insert(((10 * v + a[i][j]) * power(Z(10), n - 1)).val());
            return;
        }
        self(self, i + 1, j, 10 * v + a[i][j]);
        self(self, i, j + 1, 10 * v + a[i][j]);
    };
    pref(pref, 0, 0, 0);

    std::vector<std::set<int>> s(n);
    auto suff = [&](auto &&self, int i, int j, Z v) -> void {
        if (i + j == n - 1) {
            s[i].insert(v.val());
            return;
        }
        self(self, i - 1, j, a[i][j] * power(Z(10), 2 * (n - 1) - i - j) + v);
        self(self, i, j - 1, a[i][j] * power(Z(10), 2 * (n - 1) - i - j) + v);
    };
    suff(suff, n - 1, n - 1, 0);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        std::vector<int> a, b;
        for (auto v : p[i]) {
            a.push_back(v);
        }
        for (auto v : s[i]) {
            b.push_back(v);
        }
        for (int i = 0, j = b.size() - 1; i < a.size(); i++) {
            while (j >= 0 && a[i] + b[j] >= m) {
                j--;
            }
            if (j >= 0) {
                ans = std::max(ans, a[i] + b[j]);
            }
            ans = std::max(ans, (a[i] + b.back()) % m);
        }
    }
    std::cout << ans << "\n";

    return 0;
}
