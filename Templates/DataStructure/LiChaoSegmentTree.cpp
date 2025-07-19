template <class T, T inf, class C = std::less<>> struct LiChaoSegmentTree {
    static constexpr C cmp = {};
    struct Line {
        T k, b;
        constexpr Line(T k = 0, T b = std::max(-inf, inf, cmp)) : k{k}, b{b} {}
        constexpr T operator()(T x) const {
            return k * x + b;
        }
    };
    struct Node {
        Node *l, *r;
        Line f;
        Node() : l{}, r{}, f{} {}
    };
    int n;
    Node *t;
    LiChaoSegmentTree(int n = 0) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        t = nullptr;
    }
    void insert(Node *&p, int l, int r, int x, int y, Line f) {
        if (l >= y || r <= x) {
            return;
        }
        if (p == nullptr) {
            p = new Node();
        }
        int m = (l + r) / 2;
        if (l >= x && r <= y) {
            if (cmp(f(m), p->f(m))) {
                std::swap(f, p->f);
            }
            if (r - l == 1) {
                return;
            }
            if (cmp(f(l), p->f(l))) {
                insert(p->l, l, m, x, y, f);
            } else {
                insert(p->r, m, r, x, y, f);
            }
        } else {
            insert(p->l, l, m, x, y, f);
            insert(p->r, m, r, x, y, f);
        }
    }
    void insert(int l, int r, Line f) {
        insert(t, 0, n, l, r, f);
    }
    void insert(Line f) {
        insert(t, 0, n, 0, n, f);
    }
    T query(Node *p, int l, int r, int x) {
        if (p == nullptr) {
            return Line()(x);
        }
        if (r - l == 1) {
            return p->f(x);
        }
        int m = (l + r) / 2;
        if (x < m) {
            return std::min(p->f(x), query(p->l, l, m, x), cmp);
        } else {
            return std::min(p->f(x), query(p->r, m, r, x), cmp);
        }
    }
    T query(int x) {
        return query(t, 0, n, x);
    }
};
