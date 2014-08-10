#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <scene/module.h>
#include <system/factory/module.h>
#include <string/module.h>
#include <core/module.h>

#include "test_object.h"

//#pragma comment(lib, "punk_scene.lib")


using namespace Punk::Engine;

class AttributeTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(AttributeTest);
	CPPUNIT_TEST(testQueryInterface);
	CPPUNIT_TEST(testInitialize);
	CPPUNIT_TEST(testOwner);
	CPPUNIT_TEST(testName);
	CPPUNIT_TEST(testRawData);
	CPPUNIT_TEST(testSerialize);
	CPPUNIT_TEST_SUITE_END();
public:

	void testQueryInterface() {
		auto attribute = CreateAttribute();
		CPPUNIT_ASSERT(attribute.get() != nullptr);
	}

	void testInitialize() {
		auto attribute = CreateAttribute();
		attribute->Initialize("Name", System::CreateInstancePtr<ITestObjectInterface>(CLSID_TestObject, IID_ITestObjectInterface));
		CPPUNIT_ASSERT(attribute->GetName() == "Name");
		auto o = attribute->Get<ITestObjectInterface>();
		CPPUNIT_ASSERT(o.get() != nullptr);
		CPPUNIT_ASSERT(o->Get() == 0);
	}

	void testOwner() {
		auto attribute = CreateAttribute();
		CPPUNIT_ASSERT(attribute->GetOwner() == nullptr);
		auto node = CreateNode();
		attribute->SetOwner(node.get());
		CPPUNIT_ASSERT(attribute->GetOwner() == node.get());
		CPPUNIT_ASSERT(node->GetAttributesCount() == 1);
		CPPUNIT_ASSERT(node->GetAttribute(0) == attribute);
	}

	void testName() {
		auto attribute = CreateAttribute();
		CPPUNIT_ASSERT(attribute->GetName() == "");
		attribute->SetName("Name");
		CPPUNIT_ASSERT(attribute->GetName() == "Name");

	}

	void testRawData() {
		auto o = CreateObject();
		auto attribute = CreateAttribute();
		CPPUNIT_ASSERT(attribute->GetRawData().get() == nullptr);
		CPPUNIT_ASSERT(attribute->Get<ITestObjectInterface>().get() == nullptr);
		attribute->Set<ITestObjectInterface>(o);
		CPPUNIT_ASSERT(attribute->GetRawData().get() == o.get());
		CPPUNIT_ASSERT(attribute->Get<ITestObjectInterface>().get() == o.get());
	}

	void testSerialize() {
		Core::Buffer buffer;
		auto attribute = CreateAttribute();
		auto o = CreateObject();
		o->Set(15);
		attribute->SetRawData(o);
		auto serializable = Core::QueryInterfacePtr<Core::ISerializable>(attribute, Core::IID_ISerializable);
		CPPUNIT_ASSERT(serializable.get() != nullptr);
		serializable->Serialize(buffer);
		buffer.SetPosition(0);
		
		Core::Guid clsid;
		buffer.ReadPod(clsid);
		serializable = System::CreateInstancePtr<SceneModule::IAttribute>(clsid, SceneModule::IID_IAttribute);
		CPPUNIT_ASSERT(serializable.get() != nullptr);
		serializable->Deserialize(buffer);
		CPPUNIT_ASSERT(attribute->Get<ITestObjectInterface>()->Get() == 15);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(AttributeTest);
