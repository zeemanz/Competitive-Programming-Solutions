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
        a.assign(n, {});
    }
    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
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
    int select(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

constexpr int V = 3000000;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Fenwick<int> fen(V + 1);
    for (int i = 0; i <= V; i++) {
        fen.add(i, 1);
    }

    int q;
    std::cin >> q;

    while (q--) {
        int a, b;
        std::cin >> a >> b;

        if (a <= V && fen.rangeSum(a, a + 1) == 1) {
            for (int i = a; i <= V; i += a) {
                if (fen.rangeSum(i, i + 1) == 1) {
                    fen.add(i, -1);
                }
            }
        }

        std::cout << fen.select(b) << "\n";
    }

    return 0;
}
