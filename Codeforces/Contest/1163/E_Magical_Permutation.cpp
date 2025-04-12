#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

template <class U = u64> struct LinearBasis {
    int n, m;
    std::vector<U> a, b;
    LinearBasis() : n{0}, m{0} {}
    LinearBasis(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        this->m = 0;
        a.assign(n, {});
        b.assign(n, {});
    }
    void insert(U x) {
        U y = x;
        for (int i = n - 1; i >= 0; i--) {
            if (x >> i & 1) {
                if (a[i] == U()) {
                    a[i] = x;
                    b[i] = y;
                    m++;
                    return;
                }
                x ^= a[i];
            }
        }
    }
    bool contains(U x) {
        for (int i = n - 1; i >= 0; i--) {
            if (x >> i & 1) {
                if (a[i] == U()) {
                    return false;
                }
                x ^= a[i];
            }
        }
        return true;
    }
    int size() {
        return m;
    }
    int rank() {
        return n - m;
    }
    U &operator[](int i) {
        return b[i];
    }
    const U &operator[](int i) const {
        return b[i];
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<u32> S(n);
    for (auto &S : S) {
        std::cin >> S;
    }

    int x = 18;
    LinearBasis<u32> base;
    while (x > 0) {
        base.init(x);
        for (auto S : S) {
            if (S < (1U << x)) {
                base.insert(S);
            }
        }
        if (base.size() == x) {
            break;
        }
        x--;
    }

    std::vector<u32> p, vis(1U << x);
    auto dfs = [&](auto &&self, u32 d) -> void {
        p.push_back(d);
        vis[d] = 1;
        for (int i = 0; i < x; i++) {
            if (!vis[d ^ base[i]]) {
                self(self, d ^ base[i]);
            }
        }
    };
    dfs(dfs, 0);

    std::cout << x << "\n";
    for (auto p : p) {
        std::cout << p << " ";
    }

    return 0;
}
