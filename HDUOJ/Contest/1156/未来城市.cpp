#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, m;
        std::cin >> n >> m;

        std::vector<int> a(m), b(m), w(m);
        std::vector<std::set<int>> p(n);
        for (int i = 0; i < m; i++) {
            std::cin >> a[i] >> b[i] >> w[i];
            a[i]--;
            b[i]--;
            p[a[i]].insert(i);
            p[b[i]].insert(i);
        }

        std::vector<int> ord(m);
        std::iota(ord.begin(), ord.end(), 0);
        std::sort(ord.begin(), ord.end(), [&](int i, int j) { return w[i] > w[j]; });

        std::vector<int> par(n), full(n);
        std::iota(par.begin(), par.end(), 0);
        auto find = [&](int x) {
            while (x != par[x]) {
                x = par[x] = par[par[x]];
            }
            return x;
        };
        auto merge = [&](int x, int y) {
            x = find(x);
            y = find(y);
            if (x == y || (full[x] && full[y])) {
                return false;
            }
            par[y] = x;
            full[x] |= full[y];
            return true;
        };

        i64 ans = 0;
        for (auto i : ord) {
            if (merge(a[i], b[i])) {
                ans += w[i];
            } else if (!full[find(a[i])]) {
                full[find(a[i])] = 1;
                ans += w[i];
            }
        }
        std::cout << ans << "\n";
    }

    return 0;
}
