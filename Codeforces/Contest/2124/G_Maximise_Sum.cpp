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
        int n;
        std::cin >> n;

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        i64 ori = 0;
        std::vector<int> pre(n + 1);
        pre[0] = a[0] + n;
        for (int i = 0; i < n; i++) {
            pre[i + 1] = std::min(pre[i], a[i]);
            ori += pre[i + 1];
        }

        std::vector<i64> sub(n + 1);
        for (int i = n - 1; i >= 0; i--) {
            sub[i] = sub[i + 1] + pre[i + 1];
        }

        std::vector<int> stk, next(n, n);
        for (int i = 0; i < n; i++) {
            while (!stk.empty() && a[stk.back()] > a[i]) {
                next[stk.back()] = i;
                stk.pop_back();
            }
            stk.push_back(i);
        }

        std::vector<int> suf(n + 1);
        for (int i = n - 1; i >= 0; i--) {
            suf[i] = std::max(suf[i + 1], a[i]);
        }

        std::vector<int> pos;
        for (int i = n - 1; i >= 0; i--) {
            if (a[i] == suf[i]) {
                if (pos.empty() || a[i] > a[pos.back()]) {
                    pos.push_back(i);
                }
            }
        }

        int min = 2 * n;
        std::vector<int> lim(n + 1);
        std::vector<i64> sum(n + 1), ans(n + 1);
        for (int i = 0; i + 1 < n; i++) {
            if (a[i] < min) {
                lim[i + 1] = min - a[i];
                for (int j = i + 1; j < next[i]; j++) {
                    lim[j + 1] = std::min(lim[j], a[j] - a[i]);
                }
                for (int j = next[i]; j > i; j--) {
                    sum[j - 1] = sum[j] + lim[j];
                }
                for (int j : pos) {
                    if (j <= i) {
                        break;
                    }
                    int lo = i + 1, hi = next[i] + 1;
                    while (hi - lo > 1) {
                        int m = (lo + hi) / 2;
                        if (lim[m] >= a[j]) {
                            lo = m;
                        } else {
                            hi = m;
                        }
                    }
                    i64 cur = 1LL * std::min(lim[lo], a[j]) * (lo - i) + sum[lo] - sum[j] - sub[j];
                    ans[j - i] = std::max(ans[j - i], cur + ori);
                    if (a[i] + a[j] >= min) {
                        break;
                    }
                }
            }
            min = std::min(min, a[i]);
        }

        for (int i = n - 1; i >= 0; i--) {
            ans[i] = std::max(ans[i], ans[i + 1]);
        }
        ans[0] = std::max(ans[0], ori);
        for (int i = 0; i < n; i++) {
            std::cout << ans[i] << " \n"[i + 1 == n];
        }
    }

    return 0;
}
