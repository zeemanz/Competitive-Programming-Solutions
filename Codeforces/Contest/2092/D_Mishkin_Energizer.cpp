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

        std::string s;
        std::cin >> s;

        std::vector<int> a;
        for (auto c : s) {
            if (c == 'L') {
                a.push_back(0);
            } else if (c == 'I') {
                a.push_back(1);
            } else {
                a.push_back(2);
            }
        }

        int cnt[3]{};
        for (auto a : a) {
            cnt[a]++;
        }

        int ord[]{0, 1, 2};
        std::ranges::sort(ord, ord + 3, [&](int i, int j) { return cnt[i] < cnt[j]; });

        std::vector<int> ans;
        auto work = [&]() {
            for (int i = 0; i + 1 < a.size(); i++) {
                if (a[i] == ord[1] && a[i + 1] == ord[2]) {
                    int p = i;
                    while (cnt[ord[0]] < cnt[ord[2]]) {
                        cnt[ord[0]]++;
                        cnt[ord[1]]++;
                        ans.push_back(p);
                        ans.push_back(p + 1);
                        a.insert(a.begin() + p + 1, ord[0]);
                        a.insert(a.begin() + p + 2, ord[1]);
                        p += 2;
                    }
                } else if (a[i] == ord[2] && a[i + 1] == ord[1]) {
                    while (cnt[ord[0]] < cnt[ord[2]]) {
                        cnt[ord[0]]++;
                        cnt[ord[1]]++;
                        ans.push_back(i);
                        ans.push_back(i);
                        a.insert(a.begin() + i + 1, ord[0]);
                        a.insert(a.begin() + i + 1, ord[1]);
                    }
                } else if (a[i] == ord[0] && a[i + 1] == ord[2]) {
                    int p = i;
                    while (cnt[ord[0]] < cnt[ord[2]]) {
                        cnt[ord[1]]++;
                        cnt[ord[0]]++;
                        ans.push_back(p);
                        ans.push_back(p + 1);
                        a.insert(a.begin() + p + 1, ord[1]);
                        a.insert(a.begin() + p + 2, ord[0]);
                        p += 2;
                    }
                } else if (a[i] == ord[2] && a[i + 1] == ord[0]) {
                    while (cnt[ord[0]] < cnt[ord[2]]) {
                        cnt[ord[1]]++;
                        cnt[ord[0]]++;
                        ans.push_back(i);
                        ans.push_back(i);
                        a.insert(a.begin() + i + 1, ord[1]);
                        a.insert(a.begin() + i + 1, ord[0]);
                    }
                }
            }
        };
        work();

        std::ranges::sort(ord, ord + 3, [&](int i, int j) { return cnt[i] < cnt[j]; });
        if (cnt[ord[0]] != cnt[ord[1]]) {
            std::cout << "-1\n";
        }

        work();
        if (cnt[ord[0]] < cnt[ord[2]]) {
            std::cout << "-1\n";
        } else {
            std::cout << ans.size() << "\n";
            for (auto p : ans) {
                std::cout << p + 1 << "\n";
            }
        }
    }

    return 0;
}
