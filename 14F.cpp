/*
F. Выпуклая оболочка
ограничение по времени на тест0.5 секунд
ограничение по памяти на тест64 мегабайта
вводстандартный ввод
выводстандартный вывод
Дано N точек на плоскости. Нужно построить их выпуклую оболочку. Гарантируется, что выпуклая оболочка является невырожденной.

Входные данные
В первой строке число N (3≤N≤105). Следующие N строк содержат пары целых чисел x и y (−109≤x,y≤109) – координаты точек.

Выходные данные
В первой строке выведите N – число вершин выпуклой оболочки. Следующие N строк должны содержать координаты вершин в порядке обхода.
Никакие три подряд идущие точки не должны лежать на одной прямой.
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct Point {
	long long x;
	long long y;

	Point(const long long& x = 0, const long long& y = 0) : x(x), y(y) {};

	Point& operator+=(const Point& p);
	Point& operator-=(const Point& p);

	Point operator+(const Point& p) const;
	Point operator-(const Point& p) const;
};

Point& Point::operator+=(const Point& p) {
	x += p.x;
	y += p.y;
	return *this;
}

Point& Point::operator-=(const Point& p) {
	x -= p.x;
	y -= p.y;
	return *this;
}

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

bool SectionContainsPoint(const Point& a, const Point& b, const Point& c) {
	if (cross(a - b, a - c) != 0) {
		return false;
	}
	return ((a.x - c.x) * (b.x - c.x) <= 0 && (a.y - c.y) * (b.y - c.y) <= 0);
}

void AddPoint(std::vector<Point>& conv, Point next) {
	if (conv.size() < 2) {
		conv.push_back(next);
		return;
	}
	if (cross(conv[conv.size() - 1], next) == 0) {
		return;
	}
	while (conv.size() >= 2) {
		Point last = conv[conv.size() - 1];
		Point prev = conv[conv.size() - 2];
		if (cross(last - prev, next - last) <= 0) {
			conv.pop_back();
		}
		else {
			break;
		}
	}
	conv.push_back(next);
}

std::vector<Point> ConvexHull(const std::vector<Point>& points) {
	std::vector<Point> vert = points;
	if (vert.size() <= 2) return vert;
	Point start = vert[0];
	for (const auto& pnt : vert) {
		if (start.x > pnt.x || (start.x == pnt.x && start.y > pnt.y)) {
			start = pnt;
		}
	}
	for (auto& pnt : vert) {
		pnt -= start;
	}
	std::sort(vert.begin(), vert.end(),
		[](const Point& p1, const Point& p2) {
			return (cross(p1, p2) > 0 || SectionContainsPoint(Point(), p1, p2));
		});
	std::vector<Point> ans;
	ans.push_back(Point());
	for (int i = 0; i < int(vert.size()) - 1; ++i) {
		AddPoint(ans, vert[i]);
	}
	while (ans.size() > 2) {
		if (cross(ans[ans.size() - 2], ans[ans.size() - 1]) == 0) {
			ans.pop_back();
		}
		else {
			break;
		}
	}
	for (auto& pnt : ans) {
		pnt += start;
	}
	return ans;
}

int main() {
	int n;
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cin >> n;
	std::vector<Point> points(n);
	for (auto& p : points) {
		std::cin >> p.x >> p.y;
	}
	auto conv = ConvexHull(points);
	std::cout << conv.size() << '\n';
	for (const auto& p : conv) {
		std::cout << p.x << ' ' << p.y << '\n';
	}
}
