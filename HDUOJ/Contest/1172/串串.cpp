#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

struct SAM {
    static constexpr int SIZE = 26 + 50;
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

        std::vector<std::string> s(n);
        for (auto &s : s) {
            std::cin >> s;
        }

        SAM sam;
        std::vector<std::vector<int>> end(n);
        for (int i = 0, p = 0; i < n; i++) {
            end[i].resize(s[i].size());
            for (int j = 0; j < s[i].size(); j++) {
                p = sam.extend(p, s[i][j]);
                end[i][j] = p;
            }
            p = sam.extend(p, 26 + i);
        }

        std::vector<std::vector<int>> adj(sam.size());
        for (int i = 1; i < sam.size(); i++) {
            adj[sam.link(i)].push_back(i);
        }

        std::vector<int> max(sam.size());
        auto dfs = [&](auto &&self, int u) -> void {
            for (auto v : adj[u]) {
                self(self, v);
                max[u] = std::max(max[u], max[v]);
            }
        };

        std::vector<int> cnt(sam.size());
        std::vector<i64> sum(sam.size());
        for (int i = 0; i < n; i++) {
            max.assign(sam.size(), 0);
            for (int j = 0; j < s[i].size(); j++) {
                max[end[i][j]] = std::max(max[end[i][j]], j + 1);
            }
            dfs(dfs, 0);
            for (int p = 0; p < sam.size(); p++) {
                if (max[p] >= sam.len(p)) {
                    sum[p] += max[p] - sam.len(p) + 1;
                    cnt[p]++;
                }
            }
        }

        i64 ans = 0;
        for (int i = 1; i < sam.size(); i++) {
            if (cnt[i] > 1) {
                ans = std::max(ans, sam.len(i) * sum[i]);
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
