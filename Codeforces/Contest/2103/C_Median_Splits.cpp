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
        int n, k;
        std::cin >> n >> k;

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        std::vector<int> b(n);
        for (int i = 0; i < n; i++) {
            if (a[i] <= k) {
                b[i] = 1;
            } else {
                b[i] = -1;
            }
        }

        std::vector<int> sum(n + 1);
        for (int i = 0; i < n; i++) {
            sum[i + 1] = sum[i] + b[i];
        }

        std::priority_queue<int> lo;
        std::priority_queue<int, std::vector<int>, std::greater<>> hi;
        std::vector<int> pref(n + 1), suff(n + 1);
        for (int i = 0; i < n; i++) {
            lo.push(a[i]);
            while (lo.size() > hi.size() + 1) {
                hi.push(lo.top());
                lo.pop();
            }
            pref[i + 1] = lo.top();
        }
        while (!lo.empty()) {
            lo.pop();
        }
        while (!hi.empty()) {
            hi.pop();
        }
        for (int i = n - 1; i >= 0; i--) {
            lo.push(a[i]);
            while (lo.size() > hi.size() + 1) {
                hi.push(lo.top());
                lo.pop();
            }
            suff[i] = lo.top();
        }

        bool ok = false;
        std::multiset<int> s;
        for (int i = 1; i < n; i++) {
            s.insert(suff[i]);
        }

        std::multiset<int> p, q;
        for (int i = 1; i < n; i++) {
            if (suff[i] <= k) {
                p.insert(sum[i]);
            } else {
                q.insert(sum[i]);
            }
        }
        for (int i = 1; i <= n; i++) {
            s.extract(suff[i]);
            if (suff[i] <= k) {
                p.extract(sum[i]);
            } else {
                q.extract(sum[i]);
            }
            if (pref[i] <= k && !s.empty()) {
                if (*s.begin() <= k) {
                    ok = true;
                } else if (!q.empty() && *q.rbegin() - sum[i] >= 0) {
                    ok = true;
                }
            }
            if (pref[i] > k) {
                if (!p.empty() && *p.rbegin() - sum[i] >= 0) {
                    ok = true;
                }
            }
        }

        if (ok) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
