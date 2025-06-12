#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

struct SAM {
    static constexpr int SIZE = 26;
    static constexpr char OFFSET = 'a';
    struct Node {
        int len;
        int link;
        std::array<int, SIZE> next;
        Node() : len{}, link{}, next{} {}
    };
    std::vector<Node> t;
    SAM() {
        init();
    }
    void init() {
        t.assign(1, {});
        t[0].link = -1;
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int extend(int p, int x) {
        if (p == -1) {
            return 0;
        }
        if (t[p].next[x]) {
            int q = t[p].next[x];
            if (t[q].len == t[p].len + 1) {
                return q;
            }
            int r = newNode();
            t[r].len = t[p].len + 1;
            t[r].link = t[q].link;
            t[r].next = t[q].next;
            t[q].link = r;
            while (p != -1 && t[p].next[x] == q) {
                t[p].next[x] = r;
                p = t[p].link;
            }
            return r;
        }
        int q = newNode();
        t[q].len = t[p].len + 1;
        while (p != -1 && !t[p].next[x]) {
            t[p].next[x] = q;
            p = t[p].link;
        }
        t[q].link = extend(p, x);
        return q;
    }
    int extend(int p, char c) {
        return extend(p, c - OFFSET);
    }
    int next(int p, int x) {
        return t[p].next[x];
    }
    int next(int p, char c) {
        return next(p, c - OFFSET);
    }
    int link(int p) {
        return t[p].link;
    }
    int len(int p) {
        return t[p].len;
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

        std::string s;
        std::cin >> s;

        SAM sam;
        std::vector<int> end(n + 1);
        for (int i = 0, p = 0; i < n; i++) {
            p = sam.extend(p, s[i]);
            end[i + 1] = p;
        }

        std::vector<std::vector<int>> adj(sam.size());
        for (int i = 1; i < sam.size(); i++) {
            adj[sam.link(i)].push_back(i);
        }

        std::vector<std::set<int>> pos(sam.size());
        for (int i = 0; i <= n; i++) {
            pos[end[i]].insert(i);
        }

        int ans = 0;
        auto dfs = [&](auto &&self, int u, int p = -1) -> void {
            for (auto v : adj[u]) {
                self(self, v, u);
                if (pos[u].size() < pos[v].size()) {
                    std::swap(pos[u], pos[v]);
                }
                pos[u].insert(pos[v].begin(), pos[v].end());
                pos[v].clear();
            }
            if (p != -1) {
                int l = *pos[u].begin(), r = *pos[u].rbegin();
                auto f = [&](int p) {
                    int len = std::min({p - l - 1, r - p - 1, sam.len(u)});
                    if (len > 0) {
                        return r - l + len;
                    } else {
                        return 0;
                    }
                };
                ans = std::max(ans, f(*pos[u].lower_bound((l + r) / 2)));
                ans = std::max(ans, f(*std::prev(pos[u].upper_bound((l + r) / 2))));
            }
        };
        dfs(dfs, 0);

        std::cout << ans << "\n";
    }

    return 0;
}
