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

template <int V> constexpr Z cinv = Z(V).inv();

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    std::vector<Z> p(n + 1);
    p[0] = 1;
    for (int i = 0; i < n; i++) {
        p[i + 1] = a[i] * cinv<10>;
    }

    std::vector<Z> pre(n + 2), inv(n + 2);
    pre[0] = 1;
    for (int i = 0; i <= n; i++) {
        pre[i + 1] = pre[i] * (p[i] == 1 ? 1 : 1 - p[i]);
    }
    inv[n + 1] = pre[n + 1].inv();
    for (int i = n + 1; i > 0; i--) {
        inv[i - 1] = inv[i] * (p[i - 1] == 1 ? 1 : 1 - p[i - 1]);
    }

    std::vector<int> cnt(n + 2);
    for (int i = 0; i <= n; i++) {
        cnt[i + 1] = cnt[i] + (p[i] == 1);
    }

    std::vector<int> l(n + 1);
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;

        l[y] = std::max(l[y], x);
    }
    for (int i = 1; i <= n; i++) {
        l[i] = std::max(l[i - 1], l[i]);
    }

    std::vector<Z> dp(n + 1);
    dp[0] = 1;

    Z ans = 1;
    for (int i = 1, j = 0; i <= n; i++) {
        Z sum = ans;
        while (j < l[i]) {
            if (cnt[i] - cnt[j + 1] == 0) {
                sum -= dp[j] * pre[i] * inv[j + 1];
            }
            j++;
        }
        dp[i] = ans * p[i];
        ans = sum * (1 - p[i]) + ans * p[i];
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
