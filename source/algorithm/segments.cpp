#include <string>
#include <fstream>

struct Point {
	int x{ 0 };
	int y{ 0 };
};

struct Segment {
	Point a;
	Point b;
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


Segment s1;
Segment s2;

std::ifstream input("segments.in");
std::ofstream output("segments.out");

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

Relation classify_line_segment(const Segment& l, const Segment& r) {
	auto s1 = classify_point(l, r.a);
	auto s2 = classify_point(l, r.b);

	if (s1 == Relation::Left && s2 == Relation::Left)
		return Relation::NoCross;
	if (s1 == Relation::Right && s2 == Relation::Right)
		return Relation::NoCross;
	if (s1 == Relation::BeforeStart && s2 == Relation::BeforeStart)
		return Relation::NoCross;
	if (s1 == Relation::AfterEnd && s2 == Relation::AfterEnd)
		return Relation::NoCross;
	
	return Relation::Cross;
}

Relation classify_segment_segment(const Segment& l, const Segment& r) {
	auto s1 = classify_line_segment(l, r);
	auto s2 = classify_line_segment(r, l);
	if (s1 == Relation::NoCross || s2 == Relation::NoCross)
		return Relation::NoCross;

	return Relation::Cross;
}

//bool segment_cross_line(Segment l, Segment s) {
//	
//	//	special case: vertical
//	if (l.a.x == l.b.x) {
//		int x = l.a.x;
//		if (s.a.x < x && s.b.x < x)
//			return false;
//		if (s.a.x > x && s.b.x > x)
//			return false;
//	}
//
//	//	special case: horizontal
//	if (l.a.y == l.b.y) {
//		int y = l.a.y;
//		if (s.a.y < y && s.b.y < y)
//			return false;
//		if (s.a.y > y && s.b.y > y)
//			return false;		
//	}
//
//	//	general calse
//	int b = l.b.x - l.a.x;
//	int a = -(l.b.y - l.a.y);
//	int c = -l.a.y*l.b.x + l.a.x*l.b.y;
//	
//	int s1 = s.a.x * a + s.a.y * b + c;
//	int s2 = s.b.x * a + s.b.y * b + c;
//	if (s1 < 0 && s2 < 0)
//		return false;
//	if (s1 > 0 && s2 > 0)
//		return false;
//
//	//	on the line. check if in segment
//	if (s1 == 0 || s2 == 0) {
//		if (s1 == 0) {
//
//			//	equal to start
//			if (l.a.x == s.a.x && l.a.y == s.a.y)
//				return true;
//			//	equal to end
//			if (l.b.x == s.a.x && l.b.y == s.a.y)
//				return true;
//
//			int x1 = l.a.x - s.a.x;
//			int y1 = l.a.y - s.a.y;
//			int x2 = l.b.x - s.a.x;
//			int y2 = l.b.y - s.a.y;
//
//			if (x1*x2 + y1*y2 < 0)
//				return true;
//		}
//
//		if (s2 == 0) {
//
//			//	equal to start
//			if (l.a.x == s.b.x && l.a.y == s.b.y)
//				return true;
//			//	equal to end
//			if (l.b.x == s.b.x && l.b.y == s.b.y)
//				return true;
//
//			int x1 = l.a.x - s.b.x;
//			int y1 = l.a.y - s.b.y;
//			int x2 = l.b.x - s.b.x;
//			int y2 = l.b.y - s.b.y;
//
//			if (x1*x2 + y1*y2 < 0)
//				return true;
//		}
//		return false;
//	}
//
//	return true;
//}
//
//bool segment_cross_segment(const Segment& s1, const Segment& s2) {
//	if (!segment_cross_line(s1, s2))
//		return false;
//	if (!segment_cross_line(s2, s1))
//		return false;
//	return true;
//}

int main() {

	input >> s1.a.x >> s1.a.y;
	input >> s1.b.x >> s1.b.y;
	input >> s2.a.x >> s2.a.y;
	input >> s2.b.x >> s2.b.y;
	
	if (classify_segment_segment(s1, s2) == Relation::Cross)
		output << "Yes" << std::endl;
	else 
		output << "No" << std::endl;
}