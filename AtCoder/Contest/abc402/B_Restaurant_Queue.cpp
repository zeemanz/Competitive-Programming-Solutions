#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    std::queue<int> que;
    while (q--) {
        int o;
        std::cin >> o;

        if (o == 1) {
            int x;
            std::cin >> x;
            que.push(x);
        } else {
            std::cout << que.front() << "\n";
            que.pop();
        }
    }

    return 0;
}
