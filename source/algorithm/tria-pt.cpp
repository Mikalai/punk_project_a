#include <fstream>

std::ifstream input("tria-pt.in");
std::ofstream output("tria-pt.out");


struct Point {
	int x{ 0 };
	int y{ 0 };
};

struct Segment {
	Point a;
	Point b;
};

struct Triangle {
	Segment a;
	Segment b;
	Segment c;
};

bool operator == (const Point& l, const Point& r) {
	return l.x == r.x && l.y == r.y;
}

enum class Relation {
	Start,
	End,
	Left,
	Right,
	BeforeStart,
	AfterEnd,
	Between,
	Cross,
	NoCross
};

Relation classify_point(const Segment& s, const Point& p) {
	if (s.a == p)
		return Relation::Start;
	if (s.b == p)
		return Relation::End;

	//	general calse
	int b = s.b.x - s.a.x;
	int a = -(s.b.y - s.a.y);
	int c = -s.a.y*s.b.x + s.a.x*s.b.y;

	int sign = p.x * a + p.y * b + c;

	if (sign < 0)
		return Relation::Left;
	if (sign > 0)
		return Relation::Right;

	Point sa;
	sa.x = s.a.x - p.x;
	sa.y = s.a.y - p.y;

	Point sb;
	sb.x = s.b.x - p.x;
	sb.y = s.b.y - p.y;

	int dot = sa.x * sb.x + sa.y * sb.y;
	if (dot > 0) {
		Point ab;
		ab.x = s.b.x - s.a.x;
		ab.y = s.b.y - s.a.y;

		int sa_dot_ab = ab.x * sa.x + ab.y * sa.y;
		if (sa_dot_ab > 0)
			return Relation::BeforeStart;

		int sb_dot_ab = ab.x * sb.x + ab.y * sb.y;
		if (sb_dot_ab < 0)
			return Relation::AfterEnd;
	}


	return Relation::Between;
}

Triangle t;
Point p;

bool classify_point(const Triangle& t, const Point& p) {

	auto s1 = classify_point(t.a, p);
	auto s2 = classify_point(t.b, p);
	auto s3 = classify_point(t.c, p);

	if (s1 == s2 && s1 == s3)
		return true;
	if (s1 == Relation::Between || s2 == Relation::Between || s3 == Relation::Between)
		return true;
	if (s1 == Relation::Start || s1 == Relation::End)
		return true;
	if (s2 == Relation::Start || s2 == Relation::End)
		return true;
	if (s3 == Relation::Start || s3 == Relation::End)
		return true;

	return false;

}

int main() {

	Point a, b, c;
	input >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> p.x >> p.y;

	Segment s1, s2, s3;
	t.a.a = a;
	t.a.b = b;

	t.b.a = b;
	t.b.b = c;

	t.c.a = c;
	t.c.b = a;
		
	if (classify_point(t, p))
		output << "In";
	else
		output << "Out";

}