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

constexpr u32 P = 998244353;
using Z = Mod32<P>;

template <int V> constexpr Z CInv = Z(V).inv();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, c;
    std::cin >> n >> c;
    c--;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }
    a[c]++;

    Z den = std::accumulate(a.begin(), a.end(), Z(0)) - 1;
    std::vector<Z> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = a[i] / den;
    }

    const int v = *std::max_element(a.begin(), a.end());
    std::vector<std::vector<int>> b(v + 1);
    for (int i = 0; i < n; i++) {
        b[a[i]].push_back(i);
    }

    Z pre = 0, suf = 0;
    for (int i = 0; i < n; i++) {
        suf += p[i];
    }

    std::vector<Z> dp(n);
    for (int i = v; i > 0; i--) {
        for (int j : b[i]) {
            dp[j] = ((a[j] - 1) / den + pre + suf - p[j]) / (1 - (suf - p[j]));
        }
        for (int j : b[i]) {
            pre += p[j] * (dp[j] + 1);
            suf -= p[j];
        }
    }

    std::cout << dp[c] << "\n";

    return 0;
}
