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

        std::vector<int> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        int t = *std::max_element(a.begin(), a.end());
        for (auto &a : a) {
            if (a == -1) {
                a = t + 1;
                break;
            }
        }

        std::vector<std::vector<int>> p(t + 1);
        for (int i = t; i >= 0; i--) {
            p[i].push_back(-1);
            for (int j = 0; j < n; j++) {
                if (a[j] > i) {
                    p[i].push_back(j);
                }
            }
            p[i].push_back(n);
        }

        std::vector<std::vector<int>> adj(n);
        for (int i = 1; i <= t; i++) {
            for (int j = 1; j + 1 < p[i].size(); j++) {
                auto cit = std::lower_bound(p[i - 1].begin(), p[i - 1].end(), p[i][j]);
                auto lit = std::next(std::lower_bound(p[i - 1].begin(), p[i - 1].end(), p[i][j - 1]));
                auto rit = std::prev(std::lower_bound(p[i - 1].begin(), p[i - 1].end(), p[i][j + 1]));
                if (i % 2 == 0) {
                    if (j == 1) {
                        while (lit != cit) {
                            adj[*lit].push_back(*std::next(lit));
                            lit++;
                        }
                    } else {
                        while (lit != cit) {
                            adj[*lit].push_back(*cit);
                            lit++;
                        }
                    }
                    if (j + 1 == p[i].size() - 1) {
                        while (rit != cit) {
                            adj[*rit].push_back(*std::prev(rit));
                            rit--;
                        }
                    } else {
                        while (rit != cit) {
                            adj[*rit].push_back(*cit);
                            rit--;
                        }
                    }
                } else {
                    if (j == 1) {
                        while (lit != cit) {
                            adj[*std::next(lit)].push_back(*lit);
                            lit++;
                        }
                    } else {
                        while (lit != cit) {
                            adj[*cit].push_back(*lit);
                            lit++;
                        }
                    }
                    if (j + 1 == p[i].size() - 1) {
                        while (rit != cit) {
                            adj[*std::prev(rit)].push_back(*rit);
                            rit--;
                        }
                    } else {
                        while (rit != cit) {
                            adj[*cit].push_back(*rit);
                            rit--;
                        }
                    }
                }
            }
        }

        std::vector<int> deg(n);
        for (int i = 0; i < n; i++) {
            for (auto j : adj[i]) {
                deg[j]++;
            }
        }

        std::queue<int> que;
        for (int i = 0; i < n; i++) {
            if (deg[i] == 0) {
                que.push(i);
            }
        }

        int x = 0;
        std::vector<int> ans(n, -1);
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            ans[i] = x++;
            for (auto j : adj[i]) {
                deg[j]--;
                if (deg[j] == 0) {
                    que.push(j);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            std::cout << ans[i] + 1 << " \n"[i == n - 1];
        }
    }

    return 0;
}
