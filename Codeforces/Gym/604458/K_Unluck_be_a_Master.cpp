#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

constexpr int O = 2E6;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, x, l, r;
        std::cin >> n >> x >> l >> r;

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        if (x >= l && x <= r) {
            std::cout << "No\n";
        } else {
            int sum = std::accumulate(a.begin(), a.end(), 0);
            if (x < l && x + sum < l) {
                std::cout << "Yes\n";
            } else if (x > r && x + sum > r) {
                std::cout << "Yes\n";
            } else if (x < l && x + sum > r) {
                std::bitset<2 * O + 1> dp, mask;
                dp[x + O] = 1;
                for (int i = 0; i < l + O; i++) {
                    mask[i] = 1;
                }
                std::sort(a.begin(), a.end());
                bool ok = false;
                for (auto a : a) {
                    if (a < 0) {
                        dp |= dp >> (-a);
                    } else {
                        for (int i = l + O - 1; i >= r + O + 1 - a; i--) {
                            if (dp[i]) {
                                ok = true;
                                break;
                            }
                        }
                        if (ok) {
                            break;
                        }
                        dp |= (dp << a) & mask;
                    }
                }
                if (ok) {
                    std::cout << "Yes\n";
                } else {
                    std::cout << "No\n";
                }
            } else if (x > r && x + sum < l) {
                std::bitset<2 * O + 1> dp, mask;
                dp[x + O] = 1;
                for (int i = r + O + 1; i <= 2 * O; i++) {
                    mask[i] = 1;
                }
                std::sort(a.begin(), a.end(), std::greater());
                bool ok = false;
                for (auto a : a) {
                    if (a > 0) {
                        dp |= dp << a;
                    } else {
                        for (int i = r + O + 1; i <= l + O - a - 1; i++) {
                            if (dp[i]) {
                                ok = true;
                                break;
                            }
                        }
                        if (ok) {
                            break;
                        }
                        dp |= (dp >> (-a)) & mask;
                    }
                }
                if (ok) {
                    std::cout << "Yes\n";
                } else {
                    std::cout << "No\n";
                }
            } else {
                std::cout << "No\n";
            }
        }
    }

    return 0;
}
