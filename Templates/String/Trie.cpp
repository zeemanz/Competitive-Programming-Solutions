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
                t[next(p, a)].len = len(p) + 1;
            }
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
