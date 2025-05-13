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
};

std::vector<int> manacher(const std::string &s) {
    std::string t{0};
    for (auto c : s) {
        t.push_back(c);
        t.push_back(0);
    }
    int n = t.size();
    std::vector<int> d(n);
    for (int i = 0, p = 0; i < n; i++) {
        if (p - (i - p) >= 0 && p + d[p] > i) {
            d[i] = std::min(d[p - (i - p)], p + d[p] - i);
        }
        while (i - d[i] >= 0 && i + d[i] < n && t[i - d[i]] == t[i + d[i]]) {
            d[i]++;
        }
        if (i + d[i] > p + d[p]) {
            p = i;
        }
    }
    return d;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::string s;
        std::cin >> s;

        auto d = manacher(s);

        i64 ans = 0;
        Fenwick<int> fen(d.size());
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> que;
        for (int i = 2; i + 2 < d.size(); i += 2) {
            while (!que.empty()) {
                auto [r, j] = que.top();
                if (r <= i) {
                    fen.add(j, -1);
                    que.pop();
                } else {
                    break;
                }
            }
            int l = i - d[i];
            ans += fen.rangeSum(std::max(l + 1, 0), d.size());
            fen.add(i, 1);
            que.emplace(i + d[i], i);
        }

        std::cout << ans << "\n";
    }

    return 0;
}
