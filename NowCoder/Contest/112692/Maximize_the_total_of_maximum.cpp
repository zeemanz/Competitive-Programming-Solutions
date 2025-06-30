#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;

std::ostream &operator<<(std::ostream &os, i128 x) {
    i128 y = x;
    if (y < 0) {
        y = -y;
    }
    std::string s;
    while (y > 0 || s.empty()) {
        s.push_back('0' + (y % 10));
        y /= 10;
    }
    if (x < 0) {
        s.push_back('-');
    }
    std::reverse(s.begin(), s.end());
    return os << s;
}

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
        T res{};
        for (int i = x; i > 0; i -= i & -i) {
            res += a[i - 1];
        }
        return res;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, k, c;
        std::cin >> n >> k >> c;

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        std::vector<i64> s(n + 1);
        for (int i = 0; i < n; i++) {
            s[i + 1] = s[i] + a[i];
        }

        auto v = s;
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
        auto id = [&](i64 x) { return std::lower_bound(v.begin(), v.end(), x) - v.begin(); };

        i128 res = 0;
        Fenwick<i128> cnt(v.size()), sum(v.size());
        cnt.add(id(0), 1);
        sum.add(id(0), 0);
        for (int i = 1; i <= n; i++) {
            int j = std::upper_bound(v.begin(), v.end(), s[i] - c) - v.begin();
            res += cnt.rangeSum(0, j) * s[i] - sum.rangeSum(0, j);
            res += cnt.rangeSum(j, v.size()) * c;
            cnt.add(id(s[i]), 1);
            sum.add(id(s[i]), s[i]);
        }

        i128 cur = 0;
        Fenwick<i128> lcnt(v.size()), lsum(v.size());
        Fenwick<i128> rcnt(v.size()), rsum(v.size());

        auto add = [&](int i) {
            int l = std::lower_bound(v.begin(), v.end(), s[i] + c - k) - v.begin();
            int r = std::lower_bound(v.begin(), v.end(), s[i] + c) - v.begin();
            cur += rsum.rangeSum(l, r) - rcnt.rangeSum(l, r) * (s[i] + c - k);
            cur += rcnt.rangeSum(r, v.size()) * k;
        };

        auto del = [&](int i) {
            int l = std::upper_bound(v.begin(), v.end(), s[i] - c) - v.begin();
            int r = std::upper_bound(v.begin(), v.end(), s[i] - c + k) - v.begin();
            cur -= lcnt.rangeSum(l, r) * (s[i] - c + k) - lsum.rangeSum(l, r);
            cur -= lcnt.rangeSum(0, l) * k;
        };

        for (int i = 1; i <= n; i++) {
            rcnt.add(id(s[i]), 1);
            rsum.add(id(s[i]), s[i]);
        }
        lcnt.add(id(s[0]), 1);
        lsum.add(id(s[0]), s[0]);
        add(0);

        i128 max = cur;
        for (int i = 1; i < n; i++) {
            del(i);
            rcnt.add(id(s[i]), -1);
            rsum.add(id(s[i]), -s[i]);
            lcnt.add(id(s[i]), 1);
            lsum.add(id(s[i]), s[i]);
            add(i);
            max = std::max(max, cur);
        }

        std::cout << res + max << "\n";
    }

    return 0;
}
