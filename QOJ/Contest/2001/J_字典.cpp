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
        std::string s;
        std::cin >> s;

        auto t = s;
        std::reverse(t.begin(), t.end());

        SAM sam;
        std::vector<int> pos;
        for (int p = 0; auto c : t) {
            p = sam.extend(p, c);
            pos.push_back(p);
        }
        std::reverse(pos.begin(), pos.end());

        std::vector<std::vector<int>> adj(sam.size());
        for (int i = 1; i < sam.size(); i++) {
            adj[sam.link(i)].push_back(i);
        }

        const int log = std::__lg(sam.size());
        std::vector par(log + 1, std::vector(sam.size(), 0));

        int cur = 0;
        std::vector<i64> sum(sam.size());
        std::vector<int> in(sam.size()), out(sam.size()), seq;
        auto dfs = [&](auto &&self, int u) -> void {
            for (int i = 0; i < log; i++) {
                par[i + 1][u] = par[i][par[i][u]];
            }
            in[u] = cur++;
            seq.push_back(u);
            for (auto v : adj[u]) {
                par[0][v] = u;
                self(self, v);
                sum[u] += sum[v] + sam.len(v) - sam.len(u);
            }
            out[u] = cur;
        };
        dfs(dfs, 0);

        i64 ans = 0;
        std::vector<int> len(sam.size());

        std::set<int> sub;
        std::vector<int> vis(sam.size());
        for (int i = 0; i < sam.size(); i++) {
            sub.insert(i);
        }

        int q;
        std::cin >> q;

        while (q--) {
            int l, r;
            std::cin >> l >> r;
            l--;

            int p = pos[l];
            for (int i = log; i >= 0; i--) {
                if (r - l <= sam.len(par[i][p])) {
                    p = par[i][p];
                }
            }

            if (len[p] > r - l) {
                ans += len[p] - (r - l);
                len[p] = r - l;
            } else if (!vis[p]) {
                vis[p] = 1;
                ans += sum[p] + sam.len(p) - (r - l) + 1;
                len[p] = r - l;

                for (auto it = sub.upper_bound(in[p]); it != sub.end() && *it < out[p]; it = sub.erase(it)) {
                    int u = seq[*it];
                    vis[u] = 1;
                    if (len[u] != 0) {
                        ans -= sum[u] + sam.len(u) - len[u] + 1;
                        len[u] = 0;
                    }
                }
            }

            std::cout << ans << " \n"[q == 0];
        }
    }

    return 0;
}
