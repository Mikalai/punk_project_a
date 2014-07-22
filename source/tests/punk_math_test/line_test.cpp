#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <math/square_root.h>
#include <math/line.h>

using namespace Punk::Engine;
using namespace Punk::Engine::Math;

class LineTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(LineTest);
	CPPUNIT_TEST(testLineData);
	CPPUNIT_TEST(testLineAccessorBase);
	CPPUNIT_TEST(testLineAccessor);
	CPPUNIT_TEST(testLineOperationsBase);
	CPPUNIT_TEST(testLine3DOperations);
	CPPUNIT_TEST(testLine2DOperations);
	CPPUNIT_TEST_SUITE_END();
public:

	void testLineData() {
		Math::LineData < float, 2 > l1;
		Math::LineData < float, 2 > l2{
			Math::Tuple < float, 2, Math::tagPoint > { 1, 2 },
			Math::Tuple < float, 2, Math::tagPoint > { 3, 4 }
		};

		Math::LineData < float, 2 > l3{
			Math::Tuple < float, 2, Math::tagPoint > { 1, 2 },
			Math::Tuple < float, 2, Math::tagVector > { 0, 4 }
		};
	}

	void testLineAccessorBase() {
		Math::LineAccessorBase < float, 2 > l1;

		CPPUNIT_ASSERT((l1.GetOrigin() == Math::Tuple < float, 2, Math::tagPoint > {0, 0}));
		CPPUNIT_ASSERT((l1.GetDestination() == Math::Tuple < float, 2, Math::tagPoint > {1, 0}));
		CPPUNIT_ASSERT((l1.GetDirection() == Math::Tuple < float, 2, Math::tagVector> {1, 0}));

		Math::LineAccessorBase < float, 2 > l2{
			Math::Tuple < float, 2, Math::tagPoint > { 1, 2 },
			Math::Tuple < float, 2, Math::tagPoint > { 3, 4 }
		};

		CPPUNIT_ASSERT((l2.GetOrigin() == Math::Tuple < float, 2, Math::tagPoint > {1, 2}));
		CPPUNIT_ASSERT((l2.GetDestination() == Math::Tuple < float, 2, Math::tagPoint > {3, 4}));
		CPPUNIT_ASSERT((l2.GetDirection() == Math::Tuple < float, 2, Math::tagVector > {Math::Sqrt(2.0f) / 2.0f, Math::Sqrt(2.0f) / 2.0f}));

		Math::LineAccessorBase < float, 2 > l3{
			Math::Tuple < float, 2, Math::tagPoint > { 1, 2 },
			Math::Tuple < float, 2, Math::tagVector > { 0, 4 }
		};

		CPPUNIT_ASSERT((l3.GetOrigin() == Math::Tuple < float, 2, Math::tagPoint > {1, 2}));
		CPPUNIT_ASSERT((l3.GetDestination() == Math::Tuple < float, 2, Math::tagPoint > {1, 6}));
		CPPUNIT_ASSERT((l3.GetDirection() == Math::Tuple < float, 2, Math::tagVector > {0, 1}));
	}

	void testLineAccessor() {
		Math::Line<float, 2> l{
			Math::Tuple < float, 2, Math::tagPoint > {1, 3},
			Math::Tuple < float, 2, Math::tagPoint > {5, 6}
		};

		CPPUNIT_ASSERT((l.PointAt(0.5f) == Math::Tuple < float, 2, Math::tagPoint > {3, 4.5f}));
		CPPUNIT_ASSERT(Math::Abs(l.GetSegmentLength() - 5.0f) < Math::Eps);
	}

	void testLineOperationsBase() {

	}

	void testLine3DOperations() {
		Math::Tuple<float, 3, Math::tagVector> o{ 1, 2, 3 };
		Math::Tuple<float, 3, Math::tagVector> offset{ 3, 4, 5 };
		Math::Tuple<float, 3, Math::tagPoint> s{ 0, 0, 0 };
		Math::Tuple<float, 3, Math::tagPoint> e{ 3, 4, 5 };

		Math::Line<float, 3> l{ s + o, e + o };

		auto p1 = s + o;
		CPPUNIT_ASSERT(l.ClassifyPoint(p1) == Math::Relation::START);
		auto p2 = e + o;
		CPPUNIT_ASSERT(l.ClassifyPoint(p2) == Math::Relation::END);
		auto p3 = s - offset + o;
		CPPUNIT_ASSERT(l.ClassifyPoint(p3) == Math::Relation::FRONT);
		auto p4 = e + offset + o;
		CPPUNIT_ASSERT(l.ClassifyPoint(p4) == Math::Relation::BACK);
		auto p5 = s + o + o;
		CPPUNIT_ASSERT(l.ClassifyPoint(p5) == Math::Relation::OUTSIDE);
		auto p6 = s + offset * 0.5f + o;
		CPPUNIT_ASSERT(l.ClassifyPoint(p6) == Math::Relation::INSIDE);

		Math::Line<float, 3> l2{
			Math::Tuple < float, 3, Math::tagPoint > {3, 4, 0} + o,
			Math::Tuple < float, 3, Math::tagPoint > {0, 0, 5} + o 
		};

		float t1, t2, dst;
		auto res = l.CrossLine(l2, t1, t2, dst);
		CPPUNIT_ASSERT(res == Math::Relation::INTERSECT);
		CPPUNIT_ASSERT(t1 == 0.5f && t2 == 0.5f && dst == 0);

		Math::Tuple<float, 3, Math::tagPoint> p7;
		l.CrossLine(l2, p7);
		CPPUNIT_ASSERT(p7 == (s + e + 2.0f * o)*0.5f);		
	}

	void testLine2DOperations() {

		Tuple<float, 2, tagVector> o{ 2, 1 };
		Tuple<float, 2, tagPoint> s{ -1, -4 };
		Tuple<float, 2, tagPoint> e{ 2, 3 };

		Line<float, 2> l1{ s + o, e + o };
		l1.Flip();
		CPPUNIT_ASSERT(l1.GetOrigin() == e + o);
		CPPUNIT_ASSERT(l1.GetDestination() == s + o);

		Line<float, 2>l2{ s, e };
		l2.Rotate();
		bool v = l2.GetOrigin() == Tuple<float, 2, tagPoint>{(-1 + 2 - 3 - 4) / 2.0f, (-4 + 3 + 1 + 2) / 2.0f};
		CPPUNIT_ASSERT(v);
		v = l2.GetDestination() == Tuple<float, 2, tagPoint>{(-1 + 2 + 3 + 4) / 2.0f, (-4 + 3 - 1 - 2) / 2.0f};
		CPPUNIT_ASSERT(v);
		
		Line<float, 2> l3{ s, e };
		Line<float, 2> l4{ s, e };
		l4.Rotate();
		float t;
		auto res = l3.CrossLine(l4, t);

		CPPUNIT_ASSERT(res == Relation::INTERSECT);
		CPPUNIT_ASSERT(t == 0.5f);

		{
			Line<float, 2> l3{ s, e };
			Line<float, 2> l4{ s + o, e + o};
			float t;
			auto res = l3.CrossLine(l4, t);

			CPPUNIT_ASSERT(res == Relation::PARALLEL);
		}

		{
			Line<float, 2> l3{ s, e };
			Line<float, 2> l4{ s + (s - e), e + (s - e)};
			float t;
			auto res = l3.CrossLine(l4, t);

			CPPUNIT_ASSERT(res == Relation::ON);
		}
	}
};


CPPUNIT_TEST_SUITE_REGISTRATION(LineTest);
