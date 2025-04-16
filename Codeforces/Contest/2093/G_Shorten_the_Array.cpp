#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

struct Trie {
    static constexpr int SIZE = 2, WIDTH = 31;
    struct Node {
        int idx;
        std::array<int, SIZE> next;
        Node() : idx{-1}, next{} {}
    };
    std::vector<Node> t;
    Trie() {
        init();
    }
    void init() {
        t.assign(1, {});
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    void add(int idx, u32 x) {
        for (int p = 0, i = WIDTH - 1; i >= 0; i--) {
            u32 b = x >> i & 1;
            if (t[p].next[b] == 0) {
                t[p].next[b] = newNode();
            }
            p = t[p].next[b];
            t[p].idx = idx;
        }
    }
    int query(u32 x, u32 k) {
        int p = 0, res = -1;
        for (int i = WIDTH - 1; i >= 0; i--) {
            u32 b = (x ^ k) >> i & 1;
            if (k >> i & 1) {
                p = t[p].next[b];
                if (p == 0) {
                    break;
                }
            } else {
                res = std::max(res, t[t[p].next[b ^ 1]].idx);
                p = t[p].next[b];
                if (p == 0) {
                    break;
                }
            }
        }
        return std::max(res, t[p].idx);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        u32 k;
        std::cin >> n >> k;

        std::vector<u32> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        int ans = n + 1;
        Trie t;
        for (int i = 0; i < n; i++) {
            t.add(i, a[i]);
            int j = t.query(a[i], k);
            if (j != -1) {
                ans = std::min(ans, i - j + 1);
            }
        }
        if (ans == n + 1) {
            ans = -1;
        }

        std::cout << ans << "\n";
    }

    return 0;
}
