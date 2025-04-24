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
