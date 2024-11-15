struct Line {
    long long m, c; // Line represented as y = mx + c
    Line(long long m = 0, long long c = 0) : m(m), c(c) {}

    // Function to evaluate line y = mx + c at a given x
    long long value(long long x) const {
        return m * x + c;
    }

    // Function to determine the intersection point with another line
    double intersectX(const Line& other) const {
        return static_cast<double>(c - other.c) / (other.m - m);
    }
};

class ConvexHullTrick {
public:
    void addLine(long long m, long long c) {
        Line newLine(m, c);
        while (hull.size() >= 2 && badLine(hull[hull.size() - 2], hull.back(), newLine)) {
            hull.pop_back();
        }
        hull.push_back(newLine);
    }

    long long query(long long x) {
        if (ptr >= hull.size()) ptr = hull.size() - 1;
        while (ptr + 1 < hull.size() && hull[ptr + 1].value(x) > hull[ptr].value(x)) {
            ++ptr;
        }
        return hull[ptr].value(x);
    }

private:
    vector<Line> hull; // Stores the lines of the convex hull
    size_t ptr = 0; // Pointer to the current best line for query

    // Check if the middle line is "bad" (can be removed)
    bool badLine(const Line& l1, const Line& l2, const Line& l3) {
        return (l3.c - l1.c) * (l1.m - l2.m) <= (l2.c - l1.c) * (l1.m - l3.m);
    }
};