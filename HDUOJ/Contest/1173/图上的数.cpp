#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
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

template <int V> constexpr Z cinv = Z(V).inv();

constexpr int K = 18;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> deg(n);
    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, p;
        std::cin >> u >> v >> p;
        u--, v--;

        deg[v]++;
        adj[u].emplace_back(v, p);
    }

    std::queue<int> que;
    std::vector<std::pair<int, int>> dis(n);
    std::vector<std::vector<std::pair<int, int>>> res(n);
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            que.push(i);
        }
    }
    while (!que.empty()) {
        int u = que.front();
        que.pop();

        std::sort(res[u].begin(), res[u].end(), std::greater());
        if (res[u].size() > K) {
            res[u].resize(K);
        }

        auto [x, y] = dis[u];
        for (auto [v, p] : adj[u]) {
            deg[v]--;
            dis[v] = std::max(dis[v], {x + 1, y + p});
            if (y == 0 && p > 0) {
                res[v].emplace_back(x + 1, y + p);
            }
            if (deg[v] == 0) {
                que.push(v);
            }
        }
        for (auto [x, y] : res[u]) {
            for (auto [v, p] : adj[u]) {
                if (y + p > 0) {
                    res[v].emplace_back(x + 1, y + p);
                }
            }
        }
    }

    std::vector<int> max(n);
    for (int i = 0; i < n; i++) {
        for (auto [x, y] : res[i]) {
            max[x] = std::max(max[x], y);
        }
    }

    auto cmp = [&](int x, int y, int nx, int ny) {
        if (x == 0 || nx - x >= K) {
            return true;
        }
        i64 a = 1LL * nx * y, b = 1LL * x * ny;
        if (a <= b) {
            return true;
        }
        int d = 1 << (nx - x);
        if (a <= d * b) {
            return true;
        }
        int k = 0;
        while (i128(1 << k) * (a - d * b) < a - b) {
            k++;
        }
        return k > x;
    };

    int x = 0, y = 0;
    for (int nx = 1; nx < n; nx++) {
        if (max[nx] == 0) {
            continue;
        }
        int ny = max[nx];
        if (cmp(x, y, nx, ny)) {
            x = nx;
            y = ny;
        }
    }

    std::cout << y * cinv<10000> * (power(Z(2), x) - 1) / x << "\n";
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
