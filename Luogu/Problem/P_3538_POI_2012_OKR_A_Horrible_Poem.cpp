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

constexpr u32 P = 998244353;
using Z = Mod32<P>;

template <int V> constexpr Z inv = Z(V).inv();

struct Hash {
    static constexpr u64 B = 131, P = 917964866503;
    using H = Mod64<P>;
    inline static int m = 0;
    inline static std::vector<H> pow{1};
    int n;
    std::vector<H> hash, rhash;
    Hash(const std::string &s = {}) {
        init(s);
    }
    void init(const std::string &s) {
        n = s.size();
        if (m < n) {
            pow.resize(2 * n + 1);
            for (int i = m; i < 2 * n; i++) {
                pow[i + 1] = pow[i] * B;
            }
            m = 2 * n;
        }
        hash.assign(n + 1, 0);
        rhash.assign(n + 1, 0);
        for (int i = 0; i < n; i++) {
            hash[i + 1] = hash[i] * B + s[i];
        }
        for (int i = n - 1; i >= 0; i--) {
            rhash[i] = rhash[i + 1] * B + s[i];
        }
    }
    H get(int l, int r) {
        return hash[r] - hash[l] * pow[r - l];
    }
    H rget(int l, int r) {
        return rhash[l] - rhash[r] * pow[r - l];
    }
    int lcp(int i, int j) {
        int lo = 0, hi = n - std::max(i, j);
        while (lo < hi) {
            int x = (lo + hi + 1) / 2;
            if (get(i, i + x) == get(j, j + x)) {
                lo = x;
            } else {
                hi = x - 1;
            }
        }
        return lo;
    }
    int lcs(int i, int j) {
        int lo = 0, hi = std::min(i, j);
        while (lo < hi) {
            int x = (lo + hi + 1) / 2;
            if (get(i - x, i) == get(j - x, j)) {
                lo = x;
            } else {
                hi = x - 1;
            }
        }
        return lo;
    }
};

std::vector<int> prime, lpf;

void sieve(int n) {
    prime.clear();
    lpf.assign(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        if (lpf[i] == 0) {
            prime.push_back(i);
            lpf[i] = i;
        }
        for (auto p : prime) {
            if (i * p > n) {
                break;
            }
            lpf[i * p] = p;
            if (p == lpf[i]) {
                break;
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    sieve(n);

    std::string s;
    std::cin >> s;

    Hash h(s);

    int q;
    std::cin >> q;

    auto check = [&](int l, int r, int d) { return h.get(l, r - d) == h.get(l + d, r); };

    while (q--) {
        int l, r;
        std::cin >> l >> r;
        l--;

        int ans = r - l, len = r - l;
        while (len > 1) {
            if (check(l, r, ans / lpf[len])) {
                ans /= lpf[len];
            }
            len /= lpf[len];
        }

        std::cout << ans << "\n";
    }

    return 0;
}
