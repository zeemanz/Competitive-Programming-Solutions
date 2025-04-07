#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<i64> h(n);
    for (auto &h : h) {
        std::cin >> h;
    }

    std::vector<int> stk, left(n, -1), right(n, n);
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && h[stk.back()] < h[i]) {
            right[stk.back()] = i;
            stk.pop_back();
        }
        if (!stk.empty()) {
            left[i] = stk.back();
        }
        stk.push_back(i);
    }

    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        int cur = n;
        if (left[i] != -1) {
            cur = std::min(cur, i - left[i]);
        }
        if (right[i] != n) {
            cur = std::min(cur, right[i] - i);
        }
        if (cur < n) {
            ans += cur;
        }
    }
    std::cout << ans << "\n";

    return 0;
}
