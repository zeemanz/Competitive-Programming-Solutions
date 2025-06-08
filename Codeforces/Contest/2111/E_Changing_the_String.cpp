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
        int n, q;
        std::cin >> n >> q;

        std::string s;
        std::cin >> s;

        std::map<std::string, std::set<int>> pos;
        for (int i = 0; i < q; i++) {
            char x, y;
            std::cin >> x >> y;
            pos[{x, y}].insert(i);
        }

        for (auto &c : s) {
            if (c == 'a') {
                continue;
            } else if (c == 'b') {
                if (!pos["ba"].empty()) {
                    int i = *pos["ba"].begin();
                    pos["ba"].erase(i);
                    c = 'a';
                    continue;
                }
                if (!pos["bc"].empty() && !pos["ca"].empty()) {
                    int i = *pos["ca"].rbegin();
                    if (pos["bc"].upper_bound(i) != pos["bc"].begin()) {
                        int j = *std::prev(pos["bc"].upper_bound(i));
                        pos["ca"].erase(i);
                        pos["bc"].erase(j);
                        c = 'a';
                    }
                }
            } else {
                if (!pos["ca"].empty()) {
                    int i = *pos["ca"].begin();
                    pos["ca"].erase(i);
                    c = 'a';
                    continue;
                }
                if (!pos["cb"].empty() && !pos["ba"].empty()) {
                    int i = *pos["ba"].rbegin();
                    if (pos["cb"].upper_bound(i) != pos["cb"].begin()) {
                        int j = *std::prev(pos["cb"].upper_bound(i));
                        pos["ba"].erase(i);
                        pos["cb"].erase(j);
                        c = 'a';
                        continue;
                    }
                }
                if (!pos["cb"].empty()) {
                    int i = *pos["cb"].rbegin();
                    pos["cb"].erase(i);
                    c = 'b';
                }
            }
        }

        std::cout << s << "\n";
    }

    return 0;
}
