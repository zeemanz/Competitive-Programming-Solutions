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

constexpr u64 B = 821, P = 264738437672017;
using Z = Mod64<P>;

template <int V> constexpr Z inv = Z(V).inv();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::string s, t;
    std::cin >> s >> t;

    std::vector<Z> pow(std::max(n, m) + 1);
    pow[0] = 1;
    for (int i = 0; i + 1 < pow.size(); i++) {
        pow[i + 1] = pow[i] * B;
    }

    std::vector<Z> hs(n + 1), ht(m + 1);
    for (int i = 0; i < n; i++) {
        hs[i + 1] = hs[i] * B + s[i];
    }
    for (int i = 0; i < m; i++) {
        ht[i + 1] = ht[i] * B + t[i];
    }

    auto get = [&](auto &&hash, int l, int r) { return hash[r] - hash[l] * pow[r - l]; };

    std::map<Z, std::vector<int>> occ;
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j <= m; j++) {
            occ[get(ht, i, j)].push_back(i);
        }
    }

    int ans = n;
    for (int i = 0; i < std::min(n, m); i++) {
        if (s[i] != t[i]) {
            ans = std::min(ans, i + 2);
        }
        if (s[n - i - 1] != t[m - i - 1]) {
            ans = std::min(ans, i + 2);
        }
    }

    std::vector dp(2, std::vector(n + 1, std::vector(m + 1, n)));
    dp[0][0][0] = 0;
    for (int i = 0; i <= n; i++) {
        for (int ni = i; ni <= n; ni++) {
            for (int j = 0; j <= m; j++) {
                dp[1][ni][j] = std::min(dp[1][ni][j], dp[0][i][j] + 1);
            }
        }
        for (int ni = i + 1; ni <= n; ni++) {
            auto h = get(hs, i, ni);
            auto o = occ[h];
            for (int j = 0, k = 0; j <= m; j++) {
                while (k < o.size() && o[k] < j) {
                    k++;
                }
                if (k == o.size()) {
                    ans = std::min(ans, dp[1][i][j] + ni - i + (ni < n));
                } else {
                    if (i == 0 && j == 0 && o[k] > 0) {
                        ans = std::min(ans, ni - i + (ni < n));
                    }
                    int nj = o[k] + ni - i;
                    dp[0][ni][nj] = std::min(dp[0][ni][nj], dp[1][i][j] + ni - i);
                }
            }
        }
    }

    std::cout << ans << "\n";

    return 0;
}
