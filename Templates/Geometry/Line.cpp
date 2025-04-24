struct Line {
    Point a, b;
    Line(Point a = {}, Point b = {}) : a{a}, b{b} {}
};

// -1: 右侧
//  0: 线上
//  1: 左侧
int toLeft(Point p, Line l) {
    return sgn(cross(l.b - l.a, p - l.a));
}
bool onSegment(Point p, Line s) {
    if (toLeft(p, s) != 0) {
        return false;
    } else {
        if (sgn(std::min(s.a.x, s.b.x) - p.x) <= 0 && sgn(p.x - std::max(s.a.x, s.b.x)) <= 0) {
            return sgn(std::min(s.a.y, s.b.y) - p.y) <= 0 && sgn(p.y - std::max(s.a.y, s.b.y)) <= 0;
        } else {
            return false;
        }
    }
}
f64 distance(Point p, Line l) {
    return std::fabs(cross(l.b - l.a, p - l.a) / length(l.b - l.a));
}
f64 distance2Segment(Point p, Line s) {
    if (s.a == s.b) {
        return length(p - s.a);
    } else {
        if (sgn(dot(s.b - s.a, p - s.a)) < 0) {
            return length(p - s.a);
        } else if (sgn(dot(s.a - s.b, p - s.b)) < 0) {
            return length(p - s.b);
        } else {
            return distance(p, s);
        }
    }
}
Point project(Point p, Line l) {
    return l.a + (l.b - l.a) * dot(l.b - l.a, p - l.a) / square(l.b - l.a);
}
bool parallel(Line l1, Line l2) {
    return sgn(cross(l1.b - l1.a, l2.b - l2.a)) == 0;
}
// 0: 不相交
// 1: 正规相交
// 2: 端点相交
int segmentCrossSegment(Line s1, Line s2) {
    if (onSegment(s1.a, s2) || onSegment(s1.b, s2) || onSegment(s2.a, s1) || onSegment(s2.b, s1)) {
        return 2;
    } else {
        return toLeft(s1.a, s2) != toLeft(s1.b, s2) && toLeft(s2.a, s1) != toLeft(s2.b, s1);
    }
}
// 0: 不相交
// 1: 正规相交
// 2: 端点相交
// 3: 重合
int lineCrossSegment(Line l, Line s) {
    if (toLeft(s.a, l) == 0 && toLeft(s.b, l) == 0) {
        return 3;
    } else if (toLeft(s.a, l) == 0 || toLeft(s.b, l) == 0) {
        return 2;
    } else {
        return toLeft(s.a, l) != toLeft(s.b, l);
    }
}
// 0: 平行
// 1: 相交
// 2: 重合
int lineCrossLine(Line l1, Line l2) {
    if (parallel(l1, l2)) {
        if (toLeft(l1.a, l2) == 0) {
            return 2;
        } else {
            return 0;
        }
    } else {
        return 1;
    }
}
Point crossPoint(Line l1, Line l2) {
    f64 k = cross(l2.b - l2.a, l1.a - l2.a) / cross(l1.b - l1.a, l2.b - l2.a);
    return l1.a + k * (l1.b - l1.a);
}
