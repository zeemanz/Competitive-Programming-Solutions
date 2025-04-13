#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

template <typename T> struct Fenwick {
    int n;
    std::vector<T> a;
    Fenwick(int n = 0) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        a.assign(n, T());
    }
    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }
    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N1;
    std::cin >> N1;

    std::vector<std::vector<int>> G1(N1);
    for (int i = 0; i < N1 - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        G1[u].push_back(v);
        G1[v].push_back(u);
    }

    int N2;
    std::cin >> N2;

    std::vector<std::vector<int>> G2(N2);
    for (int i = 0; i < N2 - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        G2[u].push_back(v);
        G2[v].push_back(u);
    }

    auto dfs = [&](auto &&self, auto &&g, auto &&d, int u, int p, int &t) -> void {
        for (auto v : g[u]) {
            if (v == p) {
                continue;
            }
            d[v] = d[u] + 1;
            if (d[v] > d[t]) {
                t = v;
            }
            self(self, g, d, v, u, t);
        }
    };

    int s1 = 0;
    std::vector<int> dt1(N1);
    dfs(dfs, G1, dt1, 0, -1, s1);
    int t1 = s1;
    std::vector<int> ds1(N1);
    dfs(dfs, G1, ds1, s1, -1, t1);
    int u1 = 0;
    dt1.assign(N1, 0);
    dfs(dfs, G1, dt1, t1, -1, u1);

    int s2 = 0;
    std::vector<int> dt2(N2);
    dfs(dfs, G2, dt2, 0, -1, s2);
    int t2 = s2;
    std::vector<int> ds2(N2);
    dfs(dfs, G2, ds2, s2, -1, t2);
    int u2 = 0;
    dt2.assign(N2, 0);
    dfs(dfs, G2, dt2, t2, -1, u2);

    std::vector<int> v2(N2);
    for (int i = 0; i < N2; i++) {
        v2[i] = std::max(ds2[i], dt2[i]);
    }
    std::ranges::sort(v2);
    Fenwick<i64> f2(N2);
    for (int i = 0; i < N2; i++) {
        f2.add(i, v2[i]);
    }

    int d = std::max(ds1[t1], ds2[t2]);
    i64 ans = 1LL * N1 * N2 * d;
    for (int i = 0; i < N1; i++) {
        int x = std::max(ds1[i], dt1[i]) + 1;
        int j = std::ranges::upper_bound(v2, d - x) - v2.begin();
        if (j < N2) {
            ans -= 1LL * (N2 - j) * d;
            ans += f2.rangeSum(j, N2) + 1LL * (N2 - j) * x;
        }
    }
    std::cout << ans << "\n";

    return 0;
}
