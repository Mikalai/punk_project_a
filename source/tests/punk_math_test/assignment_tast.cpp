#include <math/forward.h>
#include <math/tuple.h>
#include <math/assignment.h>
#include <string/string.h>
#include "vec3_test.h"

using namespace Punk::Engine;
using namespace Punk::Engine;

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

struct MyPerson {
	int value;
	std::string s;
};

struct MyObject {
	int value;
	std::string s;
};

class AssignmentTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(AssignmentTest);
	CPPUNIT_TEST(testForward);
	CPPUNIT_TEST(testReverse);
	CPPUNIT_TEST(testCombined);
	CPPUNIT_TEST(testAssign);
	CPPUNIT_TEST_SUITE_END();
public:

	template<class A>
	void test1() {
		std::vector < int > cost{ 250, 400, 350, 400, 600, 350, 200, 400, 250 };
		std::vector<MyPerson> persons{ 3 };
		std::vector<MyObject> objects{ 3 };

		int k = 0;
		for (auto& p : persons) {
			p.value = k++;
			//p.location = rand() % 10;
		}

		k = 0;
		for (auto& o : objects) {
			o.value = k++;
			//o.location = rand() % 10;
		}

		Math::Auction<MyPerson, MyObject, Math::tagDenseData, A> auction;
		auction.setObjects(objects.size(), [&objects](int index) { return &objects[index]; });
		auction.setPersons(persons.size(), [&persons](int index) { return &persons[index]; });
		auction.applyCostFunction([&persons, &objects, &cost](MyPerson* p, MyObject* o) { return -cost[objects.size()*p->value + o->value]; });
		std::vector<std::pair<MyPerson*, MyObject*>> result;
		auction.run(result);
		CPPUNIT_ASSERT(result[0].second->value == 1);
		CPPUNIT_ASSERT(result[1].second->value == 2);
		CPPUNIT_ASSERT(result[2].second->value == 0);
	}

	template<class A>
	void test2() {
		std::vector < int > cost{ 90, 75, 75, 80, 35, 85, 55, 65, 125, 95, 90, 105, 45, 110, 95, 115 };
		std::vector<MyPerson> persons{ 4 };
		std::vector<MyObject> objects{ 4 };

		int k = 0;
		for (auto& p : persons) {
			p.value = k++;
			//p.location = rand() % 10;
		}

		k = 0;
		for (auto& o : objects) {
			o.value = k++;
			//o.location = rand() % 10;
		}

		Math::Auction<MyPerson, MyObject, Math::tagDenseData, A> auction;
		auction.setObjects(objects.size(), [&objects](int index) { return &objects[index]; });
		auction.setPersons(persons.size(), [&persons](int index) { return &persons[index]; });
		auction.applyCostFunction([&persons, &objects, &cost](MyPerson* p, MyObject* o) { return -cost[objects.size()*p->value + o->value]; });
		std::vector<std::pair<MyPerson*, MyObject*>> result;
		auction.run(result);
		CPPUNIT_ASSERT(result[0].second->value == 3);
		CPPUNIT_ASSERT(result[1].second->value == 2);
		CPPUNIT_ASSERT(result[2].second->value == 1);
		CPPUNIT_ASSERT(result[3].second->value == 0);
	}

	template<class A>
	void test3() {
		std::vector < int > cost{ 8, 7, 9, 9, 5, 2, 7, 8, 6, 1, 4, 9, 2, 3, 2, 6 };
		std::vector<MyPerson> persons{ 4 };
		std::vector<MyObject> objects{ 4 };

		int k = 0;
		for (auto& p : persons) {
			p.value = k++;
			//p.location = rand() % 10;
		}

		k = 0;
		for (auto& o : objects) {
			o.value = k++;
			//o.location = rand() % 10;
		}

		Math::Auction<MyPerson, MyObject, Math::tagDenseData, A> auction;
		auction.setObjects(objects.size(), [&objects](int index) { return &objects[index]; });
		auction.setPersons(persons.size(), [&persons](int index) { return &persons[index]; });
		auction.applyCostFunction([&persons, &objects, &cost](MyPerson* p, MyObject* o) { return cost[objects.size()*p->value + o->value]; });
		std::vector<std::pair<MyPerson*, MyObject*>> result;
		auction.run(result);
		CPPUNIT_ASSERT(result[0].second->value == 0);
		CPPUNIT_ASSERT(result[1].second->value == 2);
		CPPUNIT_ASSERT(result[2].second->value == 3);
		CPPUNIT_ASSERT(result[3].second->value == 1);
	}

	void testForward() {
		test1<Math::tagAlgorithmForward>();
		test2<Math::tagAlgorithmForward>();
		test3<Math::tagAlgorithmForward>();
	}

	void testReverse() {
		test1<Math::tagAlgorithmReverse>();
		test2<Math::tagAlgorithmReverse>();
		test3<Math::tagAlgorithmReverse>();
	}

	void testCombined() {
		test1<Math::tagAlgorithmCombined>();
		test2<Math::tagAlgorithmCombined>();
		test3<Math::tagAlgorithmCombined>();
	}

	void testAssign() {

	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(AssignmentTest);
