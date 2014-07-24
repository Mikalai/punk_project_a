#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <math.h>
#include <math/forward.h>
#include <math/matrix.h>
#include <string/string.h>

class Matrix3x3Test : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(Matrix3x3Test);
	CPPUNIT_TEST(testMatrix3x3);
	CPPUNIT_TEST(testIndex);
	CPPUNIT_TEST(testOperator);
	CPPUNIT_TEST(testDeterminant);
	CPPUNIT_TEST(testSwapRows);
	CPPUNIT_TEST(testChop);
	CPPUNIT_TEST(testInverse);
	CPPUNIT_TEST(testSetColumn);
	CPPUNIT_TEST(testSetRow);
	CPPUNIT_TEST(testIdentity);
	CPPUNIT_TEST(testZerofy);
	CPPUNIT_TEST(testTranslationPart);
	CPPUNIT_TEST(testRotationPart);
	CPPUNIT_TEST(testToString);
	CPPUNIT_TEST(testTranspose);
	CPPUNIT_TEST(testIsEqual);
	CPPUNIT_TEST(testNull);
	CPPUNIT_TEST(testCreate2DTranslate);
	CPPUNIT_TEST(testCreate2DRotate);
	CPPUNIT_TEST(testCreateFreeForm2DRotate);
	CPPUNIT_TEST(testCreate2DScale);
	CPPUNIT_TEST(testCreateIdentity);
	CPPUNIT_TEST(testCreate2DFreeFormScale);
	CPPUNIT_TEST(testCreate2DReflectionX);
	CPPUNIT_TEST(testCreate2DReflectionY);
	CPPUNIT_TEST(testCreate2DOriginReflection);
	CPPUNIT_TEST(testCreateFromQuaternion);
	CPPUNIT_TEST_SUITE_END();
public:
	void testMatrix3x3();
	void testIndex();
	void testOperator();
	void testDeterminant();
	void testSwapRows();
	void testChop();
	void testInverse();
	void testSetColumn();
	void testSetRow();
	void testIdentity();
	void testZerofy();
	void testTranslationPart();
	void testRotationPart();
	void testToString();
	void testTranspose();
	void testIsEqual();
	void testNull();
	void testCreate2DTranslate();
	void testCreate2DRotate();
	void testCreateFreeForm2DRotate();
	void testCreate2DScale();
	void testCreateIdentity();
	void testCreate2DFreeFormScale();
	void testCreate2DReflectionX();
	void testCreate2DReflectionY();
	void testCreate2DOriginReflection();
	void testCreateFromQuaternion();
};

CPPUNIT_TEST_SUITE_REGISTRATION(Matrix3x3Test);

using namespace Punk::Engine::Core;
using namespace Punk::Engine::Math;

void Matrix3x3Test::testMatrix3x3() {
	mat3 m1;
	CPPUNIT_ASSERT(m1 == mat3::CreateIdentity());
	mat3 m2{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (int i = 0; i < 8; ++i)
	{
		CPPUNIT_ASSERT(m2[i] == i + 1);
	}
	mat3 m3{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	for (int i = 0; i < 8; ++i)
	{
		CPPUNIT_ASSERT(m3[i] == i + 1);
	}
	vec3 v1{  1, 4, 7  };
	vec3 v2{ 2, 5, 8 };
	vec3 v3{ 3, 6, 9 };
	mat3 m4({ v1, v2, v3 });
	for (int i = 0; i < 8; ++i)
	{
		CPPUNIT_ASSERT(m3[i] == i + 1);
	}
}

void Matrix3x3Test::testIndex() {
	mat3 m{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (int i = 0; i < 9; ++i)
		CPPUNIT_ASSERT(m[i] == i + 1);

}

void Matrix3x3Test::testOperator() {
	mat3 m1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	mat3 m2{ 2, 1, 4, 3, 6, 5, 8, 7, 9 };
	mat3 sum_test{ 3, 3, 7, 7, 11, 11, 15, 15, 18 };
	CPPUNIT_ASSERT(sum_test == (m1 + m2));
	mat3 sub_test{ -1, 1, -1, 1, -1, 1, -1, 1, 0 };
	CPPUNIT_ASSERT(sub_test == (m1 - m2));
	mat3 mul_test{ 34, 41, 48, 62, 76, 90, 99, 123, 147 };
	CPPUNIT_ASSERT(mul_test == m1*m2);
	mat3 scal_mul_test{ 2, 4, 6, 8, 10, 12, 14, 16, 18 };
	CPPUNIT_ASSERT(scal_mul_test == m1*2.0f);
	CPPUNIT_ASSERT(scal_mul_test == 2.0f*m1);
	CPPUNIT_ASSERT(m1 == scal_mul_test / 2.0f);
}

void Matrix3x3Test::testDeterminant() {
	mat3 m2{ 2, 1, 4, 3, 6, 5, 8, 7, 9 };
	float d = m2.Determinant();
	CPPUNIT_ASSERT(d == -57);
}

void Matrix3x3Test::testSwapRows() {
	mat3 test{ 2, 1, 3, 5, 4, 6, 8, 7, 9 };
	mat3 m1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	m1.SwapRows(0, 1);
	CPPUNIT_ASSERT(m1 == test);
}

void Matrix3x3Test::testChop() {
	mat3 m{ 1, 2, 1e-6f, 4, 5, 6, 7, 8, 9 };
	mat3 test{ 1, 2, 0, 4, 5, 6, 7, 8, 9 };
	m.Chop(1e-5);
	CPPUNIT_ASSERT(m == test);
}

void Matrix3x3Test::testInverse() {
	mat3 m{ 1, 2, 3, 1, 1, 4, 1, 2, 4 };
	mat3 test{ 4, 2, -5, 0, -1, 1, -1, 0, 1 };
	CPPUNIT_ASSERT(test == m.Inversed());
	m.Inverse();
	CPPUNIT_ASSERT(test == m);
}

void Matrix3x3Test::testSetColumn() {
	mat3 test{ 1, 0, 0, 1, 2, 3, 0, 0, 1 };
	mat3 m;
	m.SetColumn(1, { 1, 2, 3 });
	CPPUNIT_ASSERT(m == test);
}

void Matrix3x3Test::testSetRow() {
	mat3 test{ 1, 1, 0, 0, 2, 0, 0, 3, 1 };
	mat3 m;
	m.SetRow(1, { 1, 2, 3 });
	CPPUNIT_ASSERT(m == test);
}

void Matrix3x3Test::testIdentity() {
	mat3 test{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	mat3 m = mat3::CreateIdentity();
	CPPUNIT_ASSERT(test == m);
}

void Matrix3x3Test::testZerofy() {
	mat3 test{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	mat3 m;
	m.Nullify();
	CPPUNIT_ASSERT(m == test);
}

void Matrix3x3Test::testTranslationPart() {
	mat3 m = mat3::CreateTranslate({ 1, 2 });
	vec2 t = m.TranslationPart();
	CPPUNIT_ASSERT(t == vec2(1, 2));
}

void Matrix3x3Test::testRotationPart() {
	float angle{ atanf(1) };
	mat3 test{ cosf(angle), sinf(angle), 0, -sinf(angle), cosf(angle), 0, 0, 0, 1 };
	mat3 m = mat3::CreateRotate(angle);
	CPPUNIT_ASSERT(m == test);
}

void Matrix3x3Test::testToString() {
}

void Matrix3x3Test::testTranspose() {
	mat3 test{ 1, 4, 7, 2, 5, 8, 3, 6, 9 };
	mat3 m{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	mat3 t = m.Transposed();
	CPPUNIT_ASSERT(t == test);
	m.Transpose();
	CPPUNIT_ASSERT(m == test);
}

void Matrix3x3Test::testIsEqual() {
	mat3 m1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	mat3 m2{ 1, 3, 3, 4, 5, 6, 7, 8, 9 };
	CPPUNIT_ASSERT(m1 == m1);
	CPPUNIT_ASSERT(m1 != m2);
}

void Matrix3x3Test::testNull() {
	mat3 test{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	CPPUNIT_ASSERT(test == mat3::Null());
}

void Matrix3x3Test::testCreate2DTranslate() {
	mat3 m = mat3::CreateTranslate({ 1, 2 });
	CPPUNIT_ASSERT(m.TranslationPart() == vec2(1, 2));
}

void Matrix3x3Test::testCreate2DRotate() {
	float angle{ atanf(1) };
	mat3 test{ cosf(angle), sinf(angle), 0, -sinf(angle), cosf(angle), 0, 0, 0, 1 };
	mat3 m = mat3::CreateRotate(angle);
	CPPUNIT_ASSERT(m == test);
}

void Matrix3x3Test::testCreateFreeForm2DRotate() {
}

void Matrix3x3Test::testCreate2DScale() {
}

void Matrix3x3Test::testCreateIdentity() {
}

void Matrix3x3Test::testCreate2DFreeFormScale() {
}

void Matrix3x3Test::testCreate2DReflectionX() {
}

void Matrix3x3Test::testCreate2DReflectionY() {
}

void Matrix3x3Test::testCreate2DOriginReflection() {
}

void Matrix3x3Test::testCreateFromQuaternion() {
	quat q{ { 1.0f, -1, 3, 2 } };
	mat3 test{ -11.0f / 15.0f, -2.0f / 15.0f, -2.0f / 3.0f,
		-2.0f / 3.0f, 1.0f / 3.0f, 2.0f / 3.0f,
		2.0f / 15.0f, 14.0f / 15.0f, -1.0f / 3.0f };
	test.Transpose();
	q.Normalize();
	mat3 m = mat3::CreateFromQuaternion(q);
	CPPUNIT_ASSERT(m == test);
}
