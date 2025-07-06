#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    int cur = 0;
    std::vector<int> ver(n + 1), pre(q + 1);
    std::vector<std::string> res(q + 1);

    while (q--) {
        int o;
        std::cin >> o;

        if (o == 1) {
            int i;
            std::cin >> i;
            i--;

            ver[i] = ver[n];
        } else if (o == 2) {
            int i;
            std::string s;
            std::cin >> i >> s;
            i--;

            cur++;
            pre[cur] = ver[i];
            res[cur] = s;
            ver[i] = cur;
        } else {
            int i;
            std::cin >> i;
            i--;

            ver[n] = ver[i];
        }
    }

    std::vector<std::string> ans;
    for (int i = ver[n]; i != 0; i = pre[i]) {
        ans.push_back(res[i]);
    }

    std::reverse(ans.begin(), ans.end());
    for (auto res : ans) {
        std::cout << res;
    }

    return 0;
}
