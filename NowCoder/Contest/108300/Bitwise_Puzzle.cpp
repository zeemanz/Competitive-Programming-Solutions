#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    u64 a, b, c;
    std::cin >> a >> b >> c;

    if (a == 0 && b == 0 && c > 0) {
        std::cout << "-1\n";
        return;
    }

    std::vector<int> ans;
    auto work = [&](int x) {
        ans.push_back(x);
        if (x == 1) {
            a <<= 1;
        } else if (x == 2) {
            b >>= 1;
        } else if (x == 3) {
            a ^= b;
        } else {
            b ^= a;
        }
    };

    auto log = [&](u64 x) {
        if (x == 0) {
            return -1;
        } else {
            return int(std::__lg(x));
        }
    };

    if (log(a) > log(b)) {
        work(4);
    } else if (log(a) < log(b)) {
        work(3);
    }

    while (log(a) < log(c)) {
        int i = log(a), j = log(b), k = log(c);
        if ((a >> j & 1) ^ (c >> (j + k - i) & 1)) {
            work(3);
        }
        work(1);
    }
    while (log(b) > log(c)) {
        int i = log(b);
        if (a >> i & 1) {
            work(3);
        }
        work(2);
    }
    while (b > 0) {
        int i = log(b);
        if ((a >> i & 1) ^ (c >> i & 1)) {
            work(3);
        }
        work(2);
    }
    work(4);

    std::cout << ans.size() << "\n";
    for (auto x : ans) {
        std::cout << x << "\n";
    }
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
