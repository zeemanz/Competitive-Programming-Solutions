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

constexpr int inf = int(1E9) + 1;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    std::vector<int> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    SAM sam;
    std::vector<int> pos(n);
    for (int i = n - 1, p = 0; i >= 0; i--) {
        p = sam.extend(p, s[i]);
        pos[i] = p;
    }

    std::vector<i64> way(n + 1), ans(n + 1, -1LL * inf * inf);
    std::vector<int> siz(sam.size()), min(sam.size(), inf), max(sam.size(), -inf);
    for (int i = 0; i < n; i++) {
        way[pos[i]] += siz[pos[i]];
        siz[pos[i]]++;
        if (min[pos[i]] != inf) {
            ans[pos[i]] = std::max(ans[pos[i]], 1LL * min[pos[i]] * a[i]);
        }
        if (max[pos[i]] != -inf) {
            ans[pos[i]] = std::max(ans[pos[i]], 1LL * max[pos[i]] * a[i]);
        }
        min[pos[i]] = std::min(min[pos[i]], a[i]);
        max[pos[i]] = std::max(max[pos[i]], a[i]);
    }

    std::vector<std::vector<int>> adj(sam.size());
    for (int i = 1; i < sam.size(); i++) {
        adj[sam.link(i)].push_back(i);
    }

    auto dfs = [&](auto &&self, int u) -> void {
        for (auto v : adj[u]) {
            self(self, v);
            way[sam.len(u)] += 1LL * siz[u] * siz[v];
            siz[u] += siz[v];
            if (min[u] != inf) {
                ans[sam.len(u)] = std::max(ans[sam.len(u)], 1LL * min[u] * min[v]);
            }
            if (max[u] != -inf) {
                ans[sam.len(u)] = std::max(ans[sam.len(u)], 1LL * max[u] * max[v]);
            }
            min[u] = std::min(min[u], min[v]);
            max[u] = std::max(max[u], max[v]);
        }
    };
    dfs(dfs, 0);

    for (int i = n - 1; i >= 0; i--) {
        way[i] += way[i + 1];
        ans[i] = std::max(ans[i], ans[i + 1]);
    }
    for (int i = 0; i < n; i++) {
        if (way[i] == 0) {
            ans[i] = 0;
        }
        std::cout << way[i] << " " << ans[i] << "\n";
    }

    return 0;
}
