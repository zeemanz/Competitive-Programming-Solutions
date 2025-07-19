#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

struct Trie {
    static constexpr int SIZE = 2;
    static constexpr int BITS = 60;
    struct Node {
        std::array<int, SIZE> next;
        Node() : next{} {}
    };
    std::vector<Node> t;
    Trie() {
        init();
    }
    void init() {
        t.emplace_back();
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int insert(u64 x) {
        int p = 0;
        for (int i = BITS - 1; i >= 0; i--) {
            int a = x >> i & 1;
            if (next(p, a) == 0) {
                t[p].next[a] = newNode();
            }
            p = next(p, a);
        }
        return p;
    }
    u64 query(u64 x) {
        u64 res = 0;
        for (int p = 0, i = BITS - 1; i >= 0; i--) {
            int a = x >> i & 1;
            if (next(p, a) != 0) {
                p = next(p, a);
            } else {
                p = next(p, a ^ 1);
                res |= 1ULL << i;
            }
        }
        return res;
    }
    int next(int p, int a) {
        return t[p].next[a];
    }
    int size() {
        return t.size();
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<u64> a(n);
        for (auto &a : a) {
            std::cin >> a;
        }

        bool ok = true;
        std::sort(a.begin(), a.end());

        Trie t;
        for (int i = 0; i < n; i++) {
            if (i > 0) {
                ok &= t.query(a[i]) > a[i];
            }
            t.insert(a[i]);
        }

        if (ok) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
