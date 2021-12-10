#include <vector>
#include <cmath>
#include <iostream>

struct Point {
	long long x;
	long long y;

	Point(const long long& x = 0, const long long& y = 0) : x(x), y(y) {};

	bool operator<(const Point& p) const;
	Point operator+(const Point& p) const;
	Point operator-(const Point& p) const;
	Point operator*(const long long& k) const;
};

bool Point::operator<(const Point& p) const {
	return (x < p.x || (x == p.x && y < p.y));
}

Point Point::operator+(const Point& p) const {
	return Point(x + p.x, y + p.y);
}

Point Point::operator-(const Point& p) const {
	return Point(x - p.x, y - p.y);
}

Point Point::operator*(const long long& k) const {
	return Point(x * k, y * k);
}

long long dot(const Point& p1, const Point& p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

long long cross(const Point& p1, const Point& p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

std::istream& operator>>(std::istream& in, Point& p) {
	in >> p.x >> p.y;
	return in;
}

class ConvexPolygon {
private:
	std::vector<Point> vert;

	friend ConvexPolygon operator+(const ConvexPolygon&, const ConvexPolygon&);
public:
	ConvexPolygon() = default;
	ConvexPolygon(const std::vector<Point>& vertices) : vert(std::vector<Point>(vertices.size())) {
		int ind = 0;
		for (int i = 1; i < size(); ++i) {
			if (vertices[i] < vertices[ind]) {
				ind = i;
			}
		}
		for (int i = 0; i < size(); ++i) {
			vert[(i - ind + size()) % size()] = vertices[i];
		}
	};

	size_t size() const {
		return vert.size();
	}
	Point operator[](size_t ind) const {
		return vert[ind];
	}
	Point& operator[](size_t ind) {
		return vert[ind];
	}
	bool containsPoint(Point point) const;
};

bool angleContainsPoint(const Point& right, const Point& center, const Point& left, const Point& point) {
	return (cross(left - center, point - center) <= 0 && cross(right - center, point - center) >= 0);
}

bool ConvexPolygon::containsPoint(Point point) const {
	if (!angleContainsPoint(vert[1], vert[0], vert[vert.size() - 1], point)) {
		return false;
	}
	int right = vert.size() - 1, left = 1;
	while (right - left > 1) {
		int mid = (left + right) / 2;
		if (angleContainsPoint(vert[mid], vert[0], vert[right], point)) {
			left = mid;
		}
		else {
			right = mid;
		}
	}
	return angleContainsPoint(vert[0], vert[right], vert[left], point);
}

ConvexPolygon operator+(const ConvexPolygon& a, const ConvexPolygon& b) {
	ConvexPolygon ans;
	int inda = 1, indb = 1;
	ans.vert.push_back(a[0] + b[0]);
	while (inda <= a.size() && indb <= b.size()) {
		Point u = a[inda % a.size()] - a[inda - 1];
		Point v = b[indb % b.size()] - b[indb - 1];
		if (cross(u, v) == 0) {
			if (inda < a.size() || indb < b.size()) {
				ans.vert.push_back(u + v);
			}
			++inda; ++indb;
			continue;
		}
		if (cross(u, v) > 0) {
			ans.vert.push_back(u);
			++inda;
		}
		else {
			ans.vert.push_back(v);
			++indb;
		}
	}
	for (int i = inda; i < a.size(); ++i) {
		ans.vert.push_back(a[i] - a[i - 1]);
	}
	for (int i = indb; i < b.size(); ++i) {
		ans.vert.push_back(b[i] - b[i - 1]);
	}
	for (int i = 1; i < ans.size(); ++i) {
		ans[i] = ans[i] + ans[i - 1];
	}
	return ans;
}

int main() {
	int n;
	std::cin >> n;
	std::vector<Point> vert(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> vert[i];
	}
	ConvexPolygon a(vert);
	std::cin >> n;
	vert.resize(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> vert[i];
	}
	ConvexPolygon b(vert);
	std::cin >> n;
	vert.resize(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> vert[i];
	}
	ConvexPolygon c(vert);
	ConvexPolygon fin = a + b + c;
	int q;
	std::cin >> q;
	for (int i = 0; i < q; ++i) {
		Point church;
		std::cin >> church;
		std::cout << (fin.containsPoint(church * 3) ? "YES" : "NO") << '\n';
	}
}