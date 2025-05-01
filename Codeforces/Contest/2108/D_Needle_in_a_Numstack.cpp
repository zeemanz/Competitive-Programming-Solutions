#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto query = [&](int i) {
        std::cout << "? " << i + 1 << std::endl;
        int res;
        std::cin >> res;
        return res - 1;
    };

    int t;
    std::cin >> t;

    while (t--) {
        int n, k;
        std::cin >> n >> k;

        if (n == 2 * k) {
            std::cout << "! " << k << " " << k << std::endl;
            continue;
        }

        std::vector<int> a(k), b(k);
        for (int i = 0; i < k; i++) {
            a[i] = query(i);
        }
        for (int i = n - 1; i >= n - k; i--) {
            b[k - (n - i)] = query(i);
        }

        std::vector<int> ra(k), rb(k);
        for (int i = 0; i < k; i++) {
            ra[a[i]] = i % k;
            rb[b[i]] = (n - k + i) % k;
        }

        if (ra == rb) {
            std::cout << "! -1" << std::endl;
            continue;
        }

        int x = 0;
        while (x < k && ra[x] == rb[x]) {
            x++;
        }

        int lo = 0, hi = (n - 1 - ra[x]) / k;
        while (lo < hi) {
            int m = (lo + hi + 1) / 2;
            if (query(ra[x] + m * k) == x) {
                lo = m;
            } else {
                hi = m - 1;
            }
        }

        int len = ra[x] + lo * k + 1, tmp = len;
        while (len < n - k) {
            int x = query(len);
            if (len % k == ra[x]) {
                len++;
                if (ra[x] != rb[x]) {
                    tmp = len;
                }
            } else {
                break;
            }
        }

        if (len == tmp || len == k) {
            std::cout << "! " << len << " " << n - len << std::endl;
        } else {
            std::cout << "! -1" << std::endl;
        }
    }

    return 0;
}
