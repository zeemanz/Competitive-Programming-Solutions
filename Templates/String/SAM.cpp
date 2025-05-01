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
