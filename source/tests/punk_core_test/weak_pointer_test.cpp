#ifndef BUFFER_TEST_H
#define BUFFER_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <core/module.h>
#include "string/string.h"
#include "string/string_list.h"

using namespace Punk::Engine;

static int g_var2 = 0;

class ProxyObject2 : public Core::IObject {
public:
	ProxyObject2()
	{
		g_var2++;
	}

	~ProxyObject2() {
		g_var2--;
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


class WeakPointerTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(WeakPointerTest);
	CPPUNIT_TEST(testPointerConstructor);
	CPPUNIT_TEST(testPointerAssignment);
	CPPUNIT_TEST(testGetter);
	CPPUNIT_TEST(testBoolConvert);
	CPPUNIT_TEST(testRelease);
	CPPUNIT_TEST(testReset);
	CPPUNIT_TEST_SUITE_END();

public:
	void testPointerConstructor() {
		g_var2 = 0;
		auto v = new ProxyObject2;
		{
			CPPUNIT_ASSERT(g_var2 == 1);
			Core::Pointer<ProxyObject2> p{ v, Core::DestroyObject };
			Core::WeakPtr<ProxyObject2> weak_p1{ p };
			CPPUNIT_ASSERT(p->m_ref_count == 1);
			{
				Core::WeakPtr<ProxyObject2> weak_p2{ weak_p1 };
				CPPUNIT_ASSERT(g_var2 == 1);
				CPPUNIT_ASSERT(p->m_ref_count == 1);
			}
			CPPUNIT_ASSERT(p->m_ref_count == 1);			
			p.reset(nullptr);
			CPPUNIT_ASSERT(weak_p1.Get() == nullptr);
		}
		CPPUNIT_ASSERT(g_var2 == 0);
	}

	void testPointerAssignment() {
		g_var2 = 0;
		auto v1 = new ProxyObject2;
		auto v2 = new ProxyObject2;
		CPPUNIT_ASSERT(g_var2 == 2);
		CPPUNIT_ASSERT(v1->m_ref_count == 0);
		CPPUNIT_ASSERT(v2->m_ref_count == 0);
		{
			Core::Pointer<ProxyObject2> p1{ v1, Core::DestroyObject };
			Core::Pointer<ProxyObject2> p2{ v2, Core::DestroyObject };
			CPPUNIT_ASSERT(p1->m_ref_count == 1);
			CPPUNIT_ASSERT(p2->m_ref_count == 1);
			p1 = p2;
			CPPUNIT_ASSERT(p1->m_ref_count == 2);
		}
		CPPUNIT_ASSERT(g_var2 == 0);

		Core::IObject* o1 = new ProxyObject2;
		auto o2 = new ProxyObject2;
		{
			Core::Pointer<Core::IObject> p1{ o1, Core::DestroyObject };
			Core::Pointer<ProxyObject2> p2{ o2, Core::DestroyObject };
			p2 = p1;
			CPPUNIT_ASSERT(p2.get() == o1);
			CPPUNIT_ASSERT(p2->m_ref_count == 2);
			CPPUNIT_ASSERT(g_var2 == 1);
		}
		CPPUNIT_ASSERT(g_var2 == 0);
	}

	void testGetter() {
		auto v1 = new ProxyObject2;
		Core::Pointer<ProxyObject2> p1{ v1, Core::DestroyObject };
		CPPUNIT_ASSERT(v1 == p1.get());
	}

	void testBoolConvert() {
		auto v1 = new ProxyObject2;
		Core::Pointer<ProxyObject2> p1{ v1, Core::DestroyObject };
		CPPUNIT_ASSERT(p1);
		Core::Pointer<ProxyObject2> p2{ nullptr, Core::DestroyObject };
		CPPUNIT_ASSERT(!p2);
	}

	void testRelease() {
		g_var2 = 0;
		auto v1 = new ProxyObject2;
		{
			Core::Pointer<ProxyObject2> p1{ v1, Core::DestroyObject };
			CPPUNIT_ASSERT(p1->m_ref_count == 1);
			p1.release();
		}
		CPPUNIT_ASSERT(v1->m_ref_count == 1);
		v1->Release();
		CPPUNIT_ASSERT(g_var2 == 0);
	}

	void testReset() {
		g_var2 = 0;
		auto v1 = new ProxyObject2;
		auto v2 = new ProxyObject2;
		CPPUNIT_ASSERT(g_var2 == 2);
		CPPUNIT_ASSERT(v1->m_ref_count == 0);
		CPPUNIT_ASSERT(v2->m_ref_count == 0);
		{
			Core::Pointer<ProxyObject2> p1{ v1, Core::DestroyObject };
			Core::Pointer<ProxyObject2> p2{ v2, Core::DestroyObject };
			CPPUNIT_ASSERT(p1->m_ref_count == 1);
			CPPUNIT_ASSERT(p2->m_ref_count == 1);
			p1.reset(p2.get());
			CPPUNIT_ASSERT(p1->m_ref_count == 2);
			CPPUNIT_ASSERT(g_var2 == 1);
		}
		CPPUNIT_ASSERT(g_var2 == 0);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(WeakPointerTest);


#endif // BUFFER_TEST_H
