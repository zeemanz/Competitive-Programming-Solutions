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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<std::vector<int>> adj(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            std::cin >> u >> v;
            u--;
            v--;

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        std::vector<int> siz(n);
        auto dfs = [&](auto &&self, int u, int p) -> void {
            siz[u] = 1;
            for (auto v : adj[u]) {
                if (v == p) {
                    continue;
                }
                self(self, v, u);
                siz[u] += siz[v];
            }
        };
        dfs(dfs, 0, -1);

        std::vector<int> cnt(n + 1);
        for (int i = 0; i < n; i++) {
            cnt[siz[i]]++;
        }

        if (cnt[1] == 1) {
            std::cout << power(Z(2), n) << "\n";
        } else if (cnt[1] == 2) {
            int x = 0;
            while (cnt[x + 1] == 2) {
                x++;
            }
            Z ans;
            for (int i = 0; i < n; i++) {
                int d = adj[i].size();
                if (i != 0) {
                    d--;
                }
                if (d == 2) {
                    if (siz[i] == 2 * x + 1) {
                        ans = power(Z(2), n - siz[i] + 2);
                    } else {
                        ans = power(Z(2), n - 2 * x - 1) * 3;
                    }
                    break;
                }
            }
            std::cout << ans << "\n";
        } else {
            std::cout << "0\n";
        }
    }

    return 0;
}
