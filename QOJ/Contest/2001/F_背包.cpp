#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;

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

constexpr u32 P = 998244353;
using Z = Mod32<P>;

template <int V> constexpr Z inv = Z(V).inv();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, m;
        std::cin >> n >> m;

        std::map<int, i64> s;
        for (int i = 0; i < n; i++) {
            int a, b;
            std::cin >> a >> b;
            s[b] += a;
        }

        i64 sum = 0;
        std::vector<std::pair<i64, int>> g;
        for (auto [k, v] : s) {
            g.emplace_back(v, k);
            sum += v;
        }
        std::reverse(g.begin(), g.end());

        Z ans = 0;
        int u = 0, v = 0;
        i128 need = 0, fill = 0;
        for (auto [k, w] : g) {
            if (need != 0) {
                if (v - w >= 60) {
                    break;
                }
                need *= 1LL << (v - w);
                if (need > sum) {
                    break;
                }
                if (need <= k) {
                    k -= need;
                    need = 0;
                    v = u;
                    fill = (fill + 1) % m;
                } else {
                    need -= k;
                    v = w;
                    continue;
                }
            }
            if (fill > 0) {
                if (u - w >= 60) {
                    break;
                }
                need = 1LL << (u - w);
                if (need > sum) {
                    break;
                }
                if ((m - fill) * need <= k) {
                    k -= (m - fill) * need;
                    need = 0;
                    fill = 0;
                    u = w;
                    v = w;
                } else {
                    fill = (fill + k / need) % m;
                    k %= need;
                    need -= k;
                    v = w;
                    continue;
                }
            }
            u = w;
            v = w;
            ans += (k + m - 1) / m * power(Z(2), w);
            fill = k % m;
            if (fill > 0) {
                need = 1;
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
