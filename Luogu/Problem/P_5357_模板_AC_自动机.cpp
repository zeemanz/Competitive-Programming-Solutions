#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

struct AhoCorasick {
    static constexpr int SIZE = 26;
    static constexpr char OFFSET = 'a';
    struct Node {
        int link, len;
        std::array<int, SIZE> next;
        Node() : link{0}, len{0}, next{} {}
    };
    std::vector<Node> t;
    AhoCorasick() {
        init();
    }
    void init() {
        t.assign(1, {});
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int insert(const std::vector<int> &a) {
        int p = 0;
        for (auto a : a) {
            if (next(p, a) == 0) {
                t[p].next[a] = newNode();
                t[next(p, a)].len = len(p) + 1;
            }
            p = next(p, a);
        }
        return p;
    }
    int insert(const std::string &s) {
        std::vector<int> a(s.size());
        for (int i = 0; i < s.size(); i++) {
            a[i] = s[i] - OFFSET;
        }
        return insert(a);
    }
    void build() {
        std::queue<int> que;
        for (int i = 0; i < SIZE; i++) {
            if (next(0, i) != 0) {
                que.push(next(0, i));
            }
        }
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int i = 0; i < SIZE; i++) {
                if (next(u, i) == 0) {
                    t[u].next[i] = next(link(u), i);
                } else {
                    t[next(u, i)].link = next(link(u), i);
                    que.push(next(u, i));
                }
            }
        }
    }
    int link(int p) {
        return t[p].link;
    }
    int len(int p) {
        return t[p].len;
    }
    int next(int p, int a) {
        return t[p].next[a];
    }
    int next(int p, char c) {
        return next(p, c - OFFSET);
    }
    int size() {
        return t.size();
    }
} ac;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::string> t(n);
    for (int i = 0; i < n; i++) {
        std::cin >> t[i];
    }

    std::string s;
    std::cin >> s;

    ac.init();
    std::vector<int> end(n);
    for (int i = 0; i < n; i++) {
        end[i] = ac.insert(t[i]);
    }
    ac.build();

    std::vector<int> cnt(ac.size());
    for (int p = 0; auto c : s) {
        p = ac.next(p, c);
        cnt[p]++;
    }

    std::vector<std::vector<int>> adj(ac.size());
    for (int i = 1; i < ac.size(); i++) {
        adj[ac.link(i)].push_back(i);
    }

    auto dfs = [&](auto &&self, int u) -> void {
        for (auto v : adj[u]) {
            self(self, v);
            cnt[u] += cnt[v];
        }
    };
    dfs(dfs, 0);

    for (int i = 0; i < n; i++) {
        std::cout << cnt[end[i]] << "\n";
    }

    return 0;
}
