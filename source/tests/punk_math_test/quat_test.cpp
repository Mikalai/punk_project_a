#ifndef QUAT_TEST_H
#define QUAT_TEST_H

#include "math/quat.h"
#include "math/mat4.h"
#include "math/mat3.h"
#include "math/matrix_helper.h"
#include "string/string.h"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace Punk::Engine::Math;
using namespace Punk::Engine::Core;

class QuaternionTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(QuaternionTest);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(testScalar);
	CPPUNIT_TEST(testVector);
	CPPUNIT_TEST(testToAngleAxis);
	CPPUNIT_TEST(testScalar);
	CPPUNIT_TEST(testVector);
	CPPUNIT_TEST(testSet);
	CPPUNIT_TEST(testXYZW);
	CPPUNIT_TEST(testInversed);
	CPPUNIT_TEST(testInverse);
	CPPUNIT_TEST(testConjugated);
	CPPUNIT_TEST(testConjugate);
	CPPUNIT_TEST(testNormalize);
	CPPUNIT_TEST(testNormalized);
	CPPUNIT_TEST(testLength);
	CPPUNIT_TEST(testSquareLength);
	CPPUNIT_TEST(testToString);
	CPPUNIT_TEST(testRotate);
	CPPUNIT_TEST(testDot);
	CPPUNIT_TEST(testIsEqual);
	CPPUNIT_TEST(testOperators);
	CPPUNIT_TEST(testToMatrix4x4);
	CPPUNIT_TEST(testToMatrix3x3);
	CPPUNIT_TEST(testCreateFromAngleAxis);
	CPPUNIT_TEST(testCreateFromMatrix4x4);
	CPPUNIT_TEST(testCreateFromMatrix3x3);
	CPPUNIT_TEST_SUITE_END();

public:

	void testConstructor() {

	}

	void testToAngleAxis() {

	}

	void testScalar() {

	}

	void testVector() {

	}

	void testSet() {

	}

	void testXYZW() {

	}

	void testInversed() {

	}

	void testInverse() {

	}

	void testConjugated() {

	}

	void testConjugate() {

	}

	void testNormalize() {

	}

	void testNormalized() {

	}

	void testLength() {

	}

	void testSquareLength() {

	}

	void testToString() {

	}

	void testRotate() {

	}

	void testDot() {

	}

	void testIsEqual() {

	}

	void testOperators() {

	}

	void testToMatrix4x4() {
		quat q{ 0.7071068286895752, 0.0, 1.483911233890467e-07, -0.7071067094802856 };
		mat4 test{ 2.0281588319903676e-07, 0.9999999403953552, 2.098567506436666e-07, 0,
			-0.9999999403953552, 2.028159258316009e-07, -2.0985672222195717e-07, 0,
			-2.098567506436666e-07, -2.0985672222195717e-07, 1.0, 0,
			0, 0, 0, 1 };
		test = test.Transposed();
		auto m = mat4::CreateFromQuaternion(q);
		CPPUNIT_ASSERT(m.IsEqual(test));
	}

	void testToMatrix3x3() {
		quat q{ 0.7071068286895752, 0.0, 1.483911233890467e-07, -0.7071067094802856 };
		mat3 test{ 2.0281588319903676e-07, 0.9999999403953552, 2.098567506436666e-07,
			-0.9999999403953552, 2.028159258316009e-07, -2.0985672222195717e-07,
			-2.098567506436666e-07, -2.0985672222195717e-07, 1.0 };
		auto m = mat3::CreateFromQuaternion(q);
		CPPUNIT_ASSERT(m.IsEqual(test));
	}

	void testCreateFromAngleAxis() {

	}

	void testCreateFromMatrix4x4() {

	}

	void testCreateFromMatrix3x3() {

	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(QuaternionTest);

#endif // QUAT_TEST_H
