#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

struct Trie {
    static constexpr int SIZE = 26;
    static constexpr char OFFSET = 'a';
    struct Node {
        bool end;
        int len, cnt;
        std::array<int, SIZE> next;
        Node() : end{false}, len{0}, cnt{0}, next{} {}
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
    int insert(const std::vector<int> &a) {
        int p = 0;
        for (auto a : a) {
            if (next(p, a) == 0) {
                t[p].next[a] = newNode();
            }
            t[next(p, a)].len = t[p].len + 1;
            p = next(p, a);
            t[p].cnt++;
        }
        t[p].end = true;
        return p;
    }
    int insert(const std::string &s) {
        std::vector<int> a(s.size());
        for (int i = 0; i < s.size(); i++) {
            a[i] = s[i] - OFFSET;
        }
        return insert(a);
    }
    bool end(int p) {
        return t[p].end;
    }
    int len(int p) {
        return t[p].len;
    }
    int cnt(int p) {
        return t[p].cnt;
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
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::string> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }

    Trie t;
    std::vector<int> end(n);
    for (int i = 0; i < n; i++) {
        end[i] = t.insert(s[i]);
    }

    auto check = [&](int i) {
        std::vector<int> deg(26);
        std::vector<std::vector<int>> adj(26);
        for (int p = 0; auto c : s[i]) {
            if (t.end(p)) {
                return false;
            }
            for (int d = 0; d < 26; d++) {
                if (d == c - 'a' || !t.next(p, d)) {
                    continue;
                }
                adj[c - 'a'].push_back(d);
                deg[d]++;
            }
            p = t.next(p, c);
        }
        std::queue<int> que;
        for (int i = 0; i < 26; i++) {
            if (deg[i] == 0) {
                que.push(i);
            }
        }
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (auto v : adj[u]) {
                deg[v]--;
                if (deg[v] == 0) {
                    que.push(v);
                }
            }
        }
        return std::count(deg.begin(), deg.end(), 0) == 26;
    };

    std::vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (check(i)) {
            ans.push_back(i);
        }
    }

    std::cout << ans.size() << "\n";
    for (auto i : ans) {
        std::cout << s[i] << "\n";
    }

    return 0;
}
