struct Convex : Polygon {
    using Polygon::Polygon;
    int lo, up;
    Convex(const std::vector<Point> &p) {
        init(p);
    }
    void init() {
        init(*this);
    }
    void init(std::vector<Point> p) {
        std::sort(p.begin(), p.end());
        p.erase(std::unique(p.begin(), p.end()), p.end());
        std::vector<Point> lo, up;
        for (auto p : p) {
            while (lo.size() > 1 && toLeft(p, {lo[lo.size() - 2], lo[lo.size() - 1]}) <= 0) {
                lo.pop_back();
            }
            while (up.size() > 1 && toLeft(p, {up[up.size() - 2], up[up.size() - 1]}) >= 0) {
                up.pop_back();
            }
            lo.emplace_back(p);
            up.emplace_back(p);
        }
        init(lo, up);
    }
    void init(const std::vector<Point> &lo, const std::vector<Point> &up) {
        clear();
        insert(end(), lo.begin(), lo.end());
        if (up.size() > 2) {
            insert(end(), up.rbegin() + 1, up.rend() - 1);
        }
        this->lo = lo.size();
        this->up = up.size();
    }
    int lower() {
        return lo;
    }
    int upper() {
        return up;
    }
    const Point &lower(int i) const {
        return (*this)[i % lo];
    }
    const Point &upper(int i) const {
        return (*this)[(i % up) + lo - 1];
    }
    friend Convex operator+(Convex lhs, Convex rhs) {
        std::vector<Point> res{lhs[0] + rhs[0]};
        lhs.emplace_back(lhs[0]);
        rhs.emplace_back(rhs[0]);
        for (int i = 0; i + 1 < lhs.size(); i++) {
            lhs[i] = lhs[i + 1] - lhs[i];
        }
        for (int i = 0; i + 1 < rhs.size(); i++) {
            rhs[i] = rhs[i + 1] - rhs[i];
        }
        lhs.pop_back();
        rhs.pop_back();
        res.resize(lhs.size() + rhs.size() + 1);
        std::merge(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), res.begin() + 1,
                   [&](Point p, Point q) { return sgn(cross(p, q)) > 0; });
        res.pop_back();
        for (int i = 0; i + 1 < res.size(); i++) {
            res[i + 1] += res[i];
        }
        return res;
    }
};
