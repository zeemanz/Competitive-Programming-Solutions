#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

template <class T> struct Fenwick {
    int n;
    std::vector<T> a;
    Fenwick(int n = 0) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        a.assign(n, {});
    }
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    T sum(int x) {
        T res = {};
        for (int i = x; i > 0; i -= i & -i) {
            res += a[i - 1];
        }
        return res;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    int select(const T &k) {
        int res = 0;
        T cur = {};
        for (int i = 1 << std::__lg(n); i > 0; i /= 2) {
            if (res + i <= n && cur + a[res + i - 1] <= k) {
                res += i;
                cur += a[res - 1];
            }
        }
        return res;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
            a--;
        }

        auto work = [&]() {
            std::vector<int> p(n);
            for (int i = 0; i < n; i++) {
                p[a[i]] = i;
            }

            std::vector<int> suf(n + 1, -1);
            for (int i = n - 1; i >= 0; i--) {
                suf[i] = std::max(suf[i + 1], p[i]);
            }

            Fenwick<int> fen(n);
            std::vector<int> cnt(n);
            for (int i = n - 1; i >= 0; i--) {
                cnt[i] = fen.sum(a[i]);
                fen.add(a[i], 1);
            }

            int ans = 1;
            for (int i = 0; i < n; i++) {
                int j = suf[a[i] + 1];
                if (j < i) {
                    continue;
                }
                ans = std::max(ans, cnt[i] - cnt[j] + 2);
            }
            return ans;
        };

        int ans = work();
        std::reverse(a.begin(), a.end());
        ans = std::max(ans, work());

        std::cout << ans << "\n";
    }

    return 0;
}
