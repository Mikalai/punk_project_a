#include <math/forward.h>
#include <math/matrix.h>
#include <string/string.h>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class Matrix4x4Test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(Matrix4x4Test);
	CPPUNIT_TEST(testMatrix4x4);
	CPPUNIT_TEST(testInversed);
	CPPUNIT_TEST(testRotationPart);
	CPPUNIT_TEST(testTranslationPart);
	CPPUNIT_TEST(testIndex);
	CPPUNIT_TEST(testSetColumn);
	CPPUNIT_TEST(testSetRow);
	CPPUNIT_TEST(testGetRow);
	CPPUNIT_TEST(testGetColumn);
	CPPUNIT_TEST(testIdentity);
	CPPUNIT_TEST(testTransposed);
	CPPUNIT_TEST(testToString);
	CPPUNIT_TEST(testOperator);
	CPPUNIT_TEST_SUITE_END();
public:
	void testMatrix4x4();
	void testInversed();
	void testRotationPart();
	void testTranslationPart();
	void testIndex();
	void testSetColumn();
	void testSetRow();
	void testGetRow();
	void testGetColumn();
	void testIdentity();
	void testTransposed();
	void testToString();
	void testOperator();
};


CPPUNIT_TEST_SUITE_REGISTRATION(Matrix4x4Test);

using namespace Punk::Engine::Core;
using namespace Punk::Engine::Math;

void Matrix4x4Test::testMatrix4x4() {
	vec4 v1{ 1, 2, 3, 4 };
	mat4 m1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	auto p1 = m1 * v1;
	CPPUNIT_ASSERT(p1 == vec4(90, 100, 110, 120));

	vec3 v2{ 1, 2, 3 };
	auto p2 = m1 * v2;
	CPPUNIT_ASSERT(p2 == vec3(0.6785714f, 0.7857143f, 0.8928571f));
}

void Matrix4x4Test::testInversed() {
	mat4 m1{ 1, 4, 3, 2, 5, 1, 7, 8, 9, 1, 11, 12, 3, 14, 5, 16 };
	auto m2 = m1.Inversed();
	mat4 m{ -0.0267857f, -1.3883929f, 0.8705357f, 0.0446429f, 0.1785714f, -0.4107143f, 0.1964286f, 0.0357143f, 0.2589286f, 0.7544643f, -0.4151786f, -0.0982143f, -0.2321429f, 0.3839286f, -0.2053571f, 0.0535714f };
	
	auto i = m2 * m1;
	CPPUNIT_ASSERT(i == mat4::CreateIdentity());
	CPPUNIT_ASSERT(m.IsEqual(m2, 1e-5));
}

void Matrix4x4Test::testRotationPart() {

}

void Matrix4x4Test::testTranslationPart() {

}

void Matrix4x4Test::testIndex() {

}

void Matrix4x4Test::testSetColumn() {

}

void Matrix4x4Test::testSetRow() {

}

void Matrix4x4Test::testGetRow() {

}

void Matrix4x4Test::testGetColumn() {

}

void Matrix4x4Test::testIdentity() {

}

void Matrix4x4Test::testTransposed() {

}

void Matrix4x4Test::testToString() {

}

void Matrix4x4Test::testOperator() {

}
