struct Polygon : std::vector<Point> {
    using vector::vector;
    Polygon(const std::vector<Point> &p) : vector(p) {}
    Point &operator[](size_t __n) {
        return std::vector<Point>::operator[](__n % size());
    }
    const Point &operator[](size_t __n) const {
        return std::vector<Point>::operator[](__n % size());
    }
};

// 两倍面积
geo_t area(const Polygon &poly) {
    geo_t res = 0;
    for (int i = 0; i < poly.size(); i++) {
        res += cross(poly[i], poly[i + 1]);
    }
    return res;
}
bool clockwise(const Polygon &poly) {
    return area(poly) < 0;
}
int windingNumber(Point p, const Polygon &poly) {
    int res = 0;
    for (int i = 0; i < poly.size(); i++) {
        if (onSegment(p, {poly[i], poly[i + 1]})) {
            return std::numeric_limits<int>::max();
        }
        if (sgn(poly[i].y - p.y) <= 0) {
            if (sgn(poly[i + 1].y - p.y) > 0) {
                if (toLeft(p, {poly[i], poly[i + 1]}) == 1) {
                    res++;
                }
            }
        } else {
            if (sgn(poly[i + 1].y - p.y) <= 0) {
                if (toLeft(p, {poly[i], poly[i + 1]}) == -1) {
                    res--;
                }
            }
        }
    }
    return res;
}
// 0: 外部
// 1: 内部
// 2: 边界
int inPolygon(Point p, const Polygon &poly) {
    int res = windingNumber(p, poly);
    if (res == std::numeric_limits<int>::max()) {
        return 2;
    } else {
        return res != 0;
    }
}
