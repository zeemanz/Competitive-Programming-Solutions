#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n, B, bias;
    std::cin >> n >> B >> bias;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    std::vector<i64> s(n + 1);
    for (int i = 0; i < n; i++) {
        s[i + 1] = s[i] + a[i];
    }

    std::vector<i64> f;
    auto check = [&](i64 k) {
        i64 max = 0;
        for (int i = 0; i < B; i++) {
            f.resize((n - i + B - 1) / B + 1);
            for (int j = i; j < n; j += B) {
                f[(j - i) / B + 1] = f[(j - i) / B] + s[std::min(j + B, n)] - s[j] - k;
            }
            for (int l = 0, r = 1; r < f.size(); r++) {
                if (f[r] - f[l] < 0) {
                    l = r;
                    continue;
                }
                if (f[r] - f[l] >= bias * k) {
                    return true;
                }
            }
        }
        return false;
    };

    i64 lo = 0, hi = 1E13;
    while (lo < hi) {
        auto k = (lo + hi + 1) / 2;
        if (check(k)) {
            lo = k;
        } else {
            hi = k - 1;
        }
    }

    std::vector<i64> num(n + 1), den(n + 1);
    for (int i = 1; i <= n; i++) {
        den[i] = bias + (i + B - 1) / B;
    }
    auto work = [&](i64 k) {
        for (int i = 0; i < B; i++) {
            f.resize((n - i + B - 1) / B + 1);
            for (int j = i; j < n; j += B) {
                f[(j - i) / B + 1] = f[(j - i) / B] + s[std::min(j + B, n)] - s[j] - k;
            }
            for (int l = 0, r = 1; r < f.size(); r++) {
                if (f[r] - f[l] < 0) {
                    l = r;
                    continue;
                }
                int len = std::min(i + r * B, n) - (i + l * B);
                num[len] = std::max(num[len], f[r] - f[l] + (r - l) * k);
            }
        }
    };
    work(lo);

    i64 x = 0, y = 1;
    for (int i = 1; i <= n; i++) {
        i64 g = std::gcd(num[i], den[i]);
        num[i] /= g;
        den[i] /= g;
        if (num[i] * y > den[i] * x) {
            x = num[i];
            y = den[i];
        }
    }

    std::cout << x << "/" << y << "\n";
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
