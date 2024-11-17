
struct Point {
    double x, y;
    Point(double _x, double _y) : x(_x), y(_y) {}
};

struct Circle {
    Point center;
    double radius;
    Circle(Point c, double r) : center(c), radius(r) {}
};

// Function to calculate the Euclidean distance between two points
double distance(const Point& p1, const Point& p2) {
    return hypot(p1.x - p2.x, p1.y - p2.y);
}

// Check if a point is inside a given circle
bool isPointInsideCircle(const Point& p, const Circle& c) {
    return distance(p, c.center) <= c.radius;
}

// Create a circle from two points
Circle circleFromTwoPoints(const Point& p1, const Point& p2) {
    Point center((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0);
    double radius = distance(p1, p2) / 2.0;
    return Circle(center, radius);
}

// Create a circle from three points using the circumcircle formula
Circle circleFromThreePoints(const Point& p1, const Point& p2, const Point& p3) {
    double ax = p1.x, ay = p1.y;
    double bx = p2.x, by = p2.y;
    double cx = p3.x, cy = p3.y;

    double d = 2 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by));
    if (d == 0) throw runtime_error("Collinear points");

    double ux = ((ax * ax + ay * ay) * (by - cy) + (bx * bx + by * by) * (cy - ay) + (cx * cx + cy * cy) * (ay - by)) / d;
    double uy = ((ax * ax + ay * ay) * (cx - bx) + (bx * bx + by * by) * (ax - cx) + (cx * cx + cy * cy) * (bx - ax)) / d;

    Point center(ux, uy);
    double radius = distance(center, p1);
    return Circle(center, radius);
}

// Welzl's algorithm to find the minimum enclosing circle
Circle welzlAlgorithm(vector<Point>& points, vector<Point> boundary = {}) {
    if (points.empty() || boundary.size() == 3) {
        if (boundary.empty()) return Circle(Point(0, 0), 0);
        if (boundary.size() == 1) return Circle(boundary[0], 0);
        if (boundary.size() == 2) return circleFromTwoPoints(boundary[0], boundary[1]);
        return circleFromThreePoints(boundary[0], boundary[1], boundary[2]);
    }

    Point p = points.back();
    points.pop_back();

    Circle d = welzlAlgorithm(points, boundary);

    if (isPointInsideCircle(p, d)) {
        points.push_back(p);
        return d;
    }

    boundary.push_back(p);
    Circle result = welzlAlgorithm(points, boundary);
    points.push_back(p);
    return result;
}

Circle findMinimumEnclosingCircle(vector<Point>& points) {
    srand(time(0));
    random_shuffle(points.begin(), points.end());
    return welzlAlgorithm(points);
}
