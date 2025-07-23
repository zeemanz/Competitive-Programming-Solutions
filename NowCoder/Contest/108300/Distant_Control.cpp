#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n, a;
    std::cin >> n >> a;

    std::string s;
    std::cin >> s;

    for (int i = 0, j = 0; i < n; i = j) {
        if (s[i] == '0') {
            while (j < n && s[j] == '0') {
                j++;
            }
            if (j - i > a) {
                for (int k = i; k < j; k++) {
                    s[k] = '1';
                }
            }
        } else {
            j++;
        }
    }

    int ans = std::count(s.begin(), s.end(), '1');
    for (int i = 0, j = 0; i < n; i = j) {
        if (s[i] == '1') {
            while (j < n && s[j] == '1') {
                j++;
            }
            if (j - i >= a) {
                ans = n;
                break;
            }
        } else {
            j++;
        }
    }

    std::cout << ans << "\n";
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
