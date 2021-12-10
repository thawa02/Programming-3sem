#include <vector>
#include <cmath>
#include <iostream>

struct Point {
	double x;
	double y;

	Point(const double& x = 0.0, const double& y = 0.0) : x(x), y(y) {};

	Point operator+(const Point& p) const;
	Point operator-(const Point& p) const;
};

Point Point::operator+(const Point& p) const {
	return Point(x + p.x, y + p.y);
}

Point Point::operator-(const Point& p) const {
	return Point(x - p.x, y - p.y);
}

double dot(const Point& p1, const Point& p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

double cross(const Point& p1, const Point& p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

std::istream& operator>>(std::istream& in, Point& p) {
	in >> p.x >> p.y;
	return in;
}

class Polygon {
private:
	std::vector<Point> vertices;
public:
	Polygon() = default;
	Polygon(const std::vector<Point>& vertices) : vertices(vertices) {};

	size_t size() const {
		return vertices.size();
	}
	bool containsPoint(Point point) const;
};

bool Polygon::containsPoint(Point point) const {
	double sum_of_angles = 0.0;
	for (size_t i = 0; i < size(); ++i) {
		Point u = point - vertices[i], v = point - vertices[(i + 1) % size()];
		if (cross(u, v) == 0 && dot(u, v) <= 0) return true;
		sum_of_angles += atan2(cross(u, v), dot(u, v));
	}
	if (fabs(sum_of_angles) > 3.1415) return true;
	else return false;
}

int main() {
	int n;
	Point p;
	std::cin >> n >> p;
	std::vector<Point> vert(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> vert[i];
	}
	Polygon m(vert);
	std::cout << (m.containsPoint(p) ? "YES" : "NO");
}