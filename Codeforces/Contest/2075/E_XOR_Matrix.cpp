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

constexpr u32 P = 998244353;
using Z = Mod32<P>;

template <int V> constexpr Z inv = Z(V).inv();

constexpr std::array<std::pair<bool, bool>, 4> p{{{0, 0}, {0, 1}, {1, 0}, {1, 1}}};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, m;
        u32 A, B;
        std::cin >> n >> m >> A >> B;

        Z ans = Z(A + 1) * (B + 1);
        ans += Z(A + 1) * (B + 1) * B * (power(Z(2), m - 1) - 1);
        ans += Z(B + 1) * (A + 1) * A * (power(Z(2), n - 1) - 1);

        int vis[29][1 << 4]{};
        Z mem[29][1 << 4]{};
        auto dfs = [&](auto &&self, int cur, bool eqa, bool eqb, bool oka, bool okb) -> Z {
            if (cur == -1) {
                return oka && okb;
            }
            if (vis[cur][eqa << 3 | eqb << 2 | oka << 1 | okb]) {
                return mem[cur][eqa << 3 | eqb << 2 | oka << 1 | okb];
            }
            vis[cur][eqa << 3 | eqb << 2 | oka << 1 | okb] = 1;
            bool upa = eqa ? A >> cur & 1 : 1;
            bool upb = eqb ? B >> cur & 1 : 1;
            Z res = 0;
            for (auto [ai, aj] : p) {
                if (aj > upa) {
                    continue;
                }
                if (!oka && ai > aj) {
                    continue;
                }
                for (auto [bi, bj] : p) {
                    if (bj > upb) {
                        continue;
                    }
                    if (!okb && bi > bj) {
                        continue;
                    }
                    if ((ai ^ aj) != (bi ^ bj)) {
                        continue;
                    }
                    res += self(self, cur - 1, eqa && aj == upa, eqb && bj == upb, oka || ai < aj, okb || bi < bj);
                }
            }
            return mem[cur][eqa << 3 | eqb << 2 | oka << 1 | okb] = res;
        };
        ans += dfs(dfs, 28, 1, 1, 0, 0) * (power(Z(2), n) - 2) * (power(Z(2), m) - 2);

        std::cout << ans << "\n";
    }

    return 0;
}
