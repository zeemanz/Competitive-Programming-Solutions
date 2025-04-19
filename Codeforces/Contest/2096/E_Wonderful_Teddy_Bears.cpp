#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    std::vector<int> e, o;
    for (int i = 0; i < n; i += 2) {
        if (s[i] == 'B') {
            e.push_back(0);
        } else {
            e.push_back(1);
        }
    }
    for (int i = 1; i < n; i += 2) {
        if (s[i] == 'B') {
            o.push_back(0);
        } else {
            o.push_back(1);
        }
    }

    i64 ans = 0;
    for (int pre = 0; auto x : e) {
        if (x == 0) {
            ans += pre;
        } else {
            pre++;
        }
    }
    for (int pre = 0; auto x : o) {
        if (x == 0) {
            ans += pre;
        } else {
            pre++;
        }
    }

    std::sort(e.begin(), e.end());
    std::sort(o.begin(), o.end());
    std::vector<int> a;
    for (int i = 0; i < e.size() && i < o.size(); i++) {
        a.push_back(e[i]);
        a.push_back(o[i]);
    }
    if (e.size() > o.size()) {
        a.push_back(e.back());
    }
    while (!a.empty() && a.back() == 1) {
        a.pop_back();
    }
    for (int pre = 0; auto a : a) {
        if (a == 0) {
            ans += (pre + 1) / 2;
        } else {
            pre++;
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
