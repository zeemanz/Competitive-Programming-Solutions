#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> x(n);
    for (int i = 0; i < n; i++) {
        int v = i;
        while (x[i].size() < 4) {
            x[i].push_back(v % 26);
            v /= 26;
        }
    }

    std::vector<std::string> s(n);
    std::map<std::string, std::vector<int>> p;
    for (int i = 0; i < n; i++) {
        p[""].push_back(i);
    }

    std::vector<std::string> que;
    for (int i = 0; i < 4; i++) {
        std::string q(n, ' ');
        for (auto [k, p] : p) {
            for (int j : p) {
                q[j] = 'a' + x[j][i];
            }
        }
        std::cout << "? " << q << std::endl;
        que.push_back(q);
        std::string a;
        std::cin >> a;
        std::map<std::string, std::vector<int>> np;
        for (int j = 0; j < n; j++) {
            s[j] += a[j];
            np[s[j]].push_back(j);
        }
        p = std::move(np);
    }

    std::cout << "! ";
    for (int i = 0; i < n; i++) {
        std::string t;
        for (int j = 0; j < 4; j++) {
            t += que[j][i];
        }
        std::cout << p[t][0] + 1 << " ";
    }
    std::cout << std::endl;

    return 0;
}
