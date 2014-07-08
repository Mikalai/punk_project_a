#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <core/module.h>
#include "string/string.h"
#include "string/string_list.h"

using namespace Punk::Engine;

static int g_var = 0;

class ProxyObject : public Core::IObject {
public:
	ProxyObject()
	{
		g_var++;
	}

	~ProxyObject() {
		g_var--;
	}

	std::uint32_t AddRef() {
		return m_ref_count++;
	}

	std::uint32_t Release() {
		auto v = --m_ref_count;
		if (!v)
			delete this;
		return v; 
	}

	void QueryInterface(const Core::Guid& value, void** object) {

	}

	std::uint32_t m_ref_count{ 0 };
};


class PointerTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(PointerTest);
	CPPUNIT_TEST(testPointerConstructor);
	CPPUNIT_TEST(testPointerAssignment);
	CPPUNIT_TEST(testGetter);
	CPPUNIT_TEST(testBoolConvert);
	CPPUNIT_TEST(testRelease);
	CPPUNIT_TEST(testReset);
	CPPUNIT_TEST_SUITE_END();

public:
	void testPointerConstructor() {
		auto v = new ProxyObject;
			{
			CPPUNIT_ASSERT(g_var == 1);
				Core::Pointer<ProxyObject> p{v, Core::DestroyObject };
				CPPUNIT_ASSERT(p->m_ref_count == 1);
				{
					Core::Pointer<ProxyObject> p2{ p };
					CPPUNIT_ASSERT(g_var == 1);
					CPPUNIT_ASSERT(p->m_ref_count == 2);
					CPPUNIT_ASSERT(p2->m_ref_count == 2);
				}
				CPPUNIT_ASSERT(p->m_ref_count == 1);
			}
		CPPUNIT_ASSERT(g_var == 0);
	}

	void testPointerAssignment() {
		g_var = 0;
		auto v1 = new ProxyObject;
		auto v2 = new ProxyObject;
		CPPUNIT_ASSERT(g_var == 2);
		CPPUNIT_ASSERT(v1->m_ref_count == 0);
		CPPUNIT_ASSERT(v2->m_ref_count == 0);
		{
			Core::Pointer<ProxyObject> p1{ v1, Core::DestroyObject };
			Core::Pointer<ProxyObject> p2{ v2, Core::DestroyObject };
			CPPUNIT_ASSERT(p1->m_ref_count == 1);
			CPPUNIT_ASSERT(p2->m_ref_count == 1);
			p1 = p2;
			CPPUNIT_ASSERT(p1->m_ref_count == 2);
		}
		CPPUNIT_ASSERT(g_var == 0);

		Core::IObject* o1 = new ProxyObject;
		auto o2 = new ProxyObject;
		{
			Core::Pointer<Core::IObject> p1{ o1, Core::DestroyObject };
			Core::Pointer<ProxyObject> p2{ o2, Core::DestroyObject };
			p2 = p1;
			CPPUNIT_ASSERT(p2.get() == o1);
			CPPUNIT_ASSERT(p2->m_ref_count == 2);
			CPPUNIT_ASSERT(g_var == 1);
		}
		CPPUNIT_ASSERT(g_var == 0);
	}

	void testGetter() {
		auto v1 = new ProxyObject;
		Core::Pointer<ProxyObject> p1{ v1, Core::DestroyObject };
		CPPUNIT_ASSERT(v1 == p1.get());
	}

	void testBoolConvert() {
		auto v1 = new ProxyObject;
		Core::Pointer<ProxyObject> p1{ v1, Core::DestroyObject };
		CPPUNIT_ASSERT(p1);
		Core::Pointer<ProxyObject> p2{ nullptr, Core::DestroyObject };
		CPPUNIT_ASSERT(!p2);
	}

	void testRelease() {
		g_var = 0;
		auto v1 = new ProxyObject;
		{
			Core::Pointer<ProxyObject> p1{ v1, Core::DestroyObject };
			CPPUNIT_ASSERT(p1->m_ref_count == 1);
			p1.release();
		}		
		CPPUNIT_ASSERT(v1->m_ref_count == 1);
		v1->Release();
		CPPUNIT_ASSERT(g_var == 0);
	}

	void testReset() {
		g_var = 0;
		auto v1 = new ProxyObject;
		auto v2 = new ProxyObject;
		CPPUNIT_ASSERT(g_var == 2);
		CPPUNIT_ASSERT(v1->m_ref_count == 0);
		CPPUNIT_ASSERT(v2->m_ref_count == 0);
		{
			Core::Pointer<ProxyObject> p1{ v1, Core::DestroyObject };
			Core::Pointer<ProxyObject> p2{ v2, Core::DestroyObject };
			CPPUNIT_ASSERT(p1->m_ref_count == 1);
			CPPUNIT_ASSERT(p2->m_ref_count == 1);
			p1.reset(p2.get());			
			CPPUNIT_ASSERT(p1->m_ref_count == 2);
			CPPUNIT_ASSERT(g_var == 1);
		}
		CPPUNIT_ASSERT(g_var == 0);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(PointerTest);

