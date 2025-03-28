#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

struct DSU {
    std::vector<int> par;
    DSU() {}
    DSU(int n) { init(n); }
    void init(int n) {
        par.resize(n);
        std::iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        while (x != par[x]) {
            x = par[x] = par[par[x]];
        }
        return x;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        par[y] = x;
        return true;
    }
};

constexpr int V = 1E6;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> primes, minp(V + 1);
    for (int i = 2; i <= V; i++) {
        if (minp[i] == 0) {
            primes.push_back(i);
            minp[i] = i;
        }
        for (auto p : primes) {
            if (i * p > V) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }

    std::vector<std::vector<int>> d(V + 1);
    for (auto p : primes) {
        for (int i = p; i <= V; i += p) {
            d[i].push_back(p);
        }
    }

    std::vector<std::vector<int>> p(V + 1);

    int t;
    std::cin >> t;

    while (t--) {
        int n, k;
        std::cin >> n >> k;

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }
        for (int i = 1; i < n; i++) {
            a.push_back(a[n - i]);
        }
        std::reverse(a.begin(), a.begin() + n);

        i64 ans = 0;
        std::vector<int> v;
        for (int i = 0; i < 2 * n - 1; i++) {
            if (a[i] == 1) {
                ans += i < n ? i + 1 : 2 * n - i - 1;
            } else {
                ans++;
            }
            for (auto d : d[a[i]]) {
                p[d].push_back(i);
                v.push_back(d);
            }
        }

        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());

        DSU dsu(2 * n - 1);
        for (auto v : v) {
            for (int i = 1; i < p[v].size(); i++) {
                int x = p[v][i - 1], y = p[v][i];
                if (y - x <= k) {
                    ans -= dsu.merge(x, y);
                }
            }
        }

        for (auto v : v) {
            p[v].clear();
        }

        std::cout << ans << "\n";
    }

    return 0;
}
