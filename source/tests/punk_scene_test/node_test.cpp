#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <scene/module.h>
#include <system/factory/module.h>
#include <string/module.h>
#include <core/module.h>

#include "test_object.h"

//#pragma comment(lib, "punk_scene.lib")

class NodeTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(NodeTest);
	CPPUNIT_TEST(testQueryInterface);
	CPPUNIT_TEST(testParent);
	CPPUNIT_TEST(testAttributes);
	CPPUNIT_TEST(testSerialize);
	CPPUNIT_TEST_SUITE_END();
public:

	void testQueryInterface() {
		auto node = CreateNode();
		CPPUNIT_ASSERT(node.get() != nullptr);
	}

	void testParent() {
		auto parent = CreateNode();
		auto child = CreateNode();
		CPPUNIT_ASSERT(parent->GetParent() == nullptr);
		CPPUNIT_ASSERT(child->GetParent() == nullptr);
		parent->AddChild(child);
		CPPUNIT_ASSERT(parent->GetChildrenCount() == 1);
		CPPUNIT_ASSERT(parent->GetChild(0) == child);
		CPPUNIT_ASSERT(child->GetParent() == parent.get());
		parent->RemoveChild(child);
		CPPUNIT_ASSERT(parent->GetChildrenCount() == 0);		
		CPPUNIT_ASSERT(child->GetParent() == nullptr);
		{
			auto n1 = CreateNode();
			auto n2 = CreateNode();
			parent->AddChild(n1);
			parent->AddChild(n2);
			CPPUNIT_ASSERT(parent->GetChildrenCount() == 2);
			CPPUNIT_ASSERT(parent->GetChild(0) == n1);
			CPPUNIT_ASSERT(parent->GetChild(1) == n2);
			CPPUNIT_ASSERT(n1->GetParent() == parent.get());
			CPPUNIT_ASSERT(n2->GetParent() == parent.get());
			parent->RemoveAllChildren();
			CPPUNIT_ASSERT(parent->GetChildrenCount() == 0);
			CPPUNIT_ASSERT(n1->GetParent() == nullptr);
			CPPUNIT_ASSERT(n2->GetParent() == nullptr);
		}
	} 

	void testAttributes() {
		auto a1 = CreateAttribute();
		a1->Initialize("A1", CreateObject());
		CPPUNIT_ASSERT(a1.get() != nullptr);
		auto a2 = CreateAttribute();
		a2->Initialize("A2", CreateObject());
		CPPUNIT_ASSERT(a2.get() != nullptr);
		auto node = CreateNode();
		CPPUNIT_ASSERT(node.get() != nullptr);
		node->AddAttribute(a1);
		node->AddAttribute(a2);
		CPPUNIT_ASSERT(node->GetAttributesCount() == 2);
		CPPUNIT_ASSERT(node->GetAttributeIndex("A1") == 0);
		CPPUNIT_ASSERT(node->GetAttributeIndex("A2") == 1);
		CPPUNIT_ASSERT(a1->GetOwner() == node.get());
		CPPUNIT_ASSERT(a2->GetOwner() == node.get());
		CPPUNIT_ASSERT(node->GetAttributesCount(IID_ITestObjectInterface) == 2);		
		node->RemoveAttribute("A1");		
		CPPUNIT_ASSERT(node->GetAttributesCount(IID_ITestObjectInterface) == 1);
		CPPUNIT_ASSERT(a1->GetOwner() == nullptr);		
		CPPUNIT_ASSERT(node->GetAttributeIndex("A2") == 0);
		node->AddAttribute(a1);
		CPPUNIT_ASSERT(node->GetAttributesCount() == 2);
		CPPUNIT_ASSERT(node->GetAttributeIndex("A2") == 0);
		CPPUNIT_ASSERT(node->GetAttributeIndex("A1") == 1);
		{
			auto root = System::CreateInstancePtr<SceneModule::INode>(SceneModule::CLSID_Node, SceneModule::IID_INode);
			auto node1 = System::CreateInstancePtr<SceneModule::INode>(SceneModule::CLSID_Node, SceneModule::IID_INode);
			auto node2 = System::CreateInstancePtr<SceneModule::INode>(SceneModule::CLSID_Node, SceneModule::IID_INode);
			auto attribute = System::CreateInstancePtr<SceneModule::IAttribute>(SceneModule::CLSID_Attribute, SceneModule::IID_IAttribute);
			root->AddChild(node1);
			root->AddChild(node2);
			attribute->SetName("Attribute");
			node1->AddAttribute(attribute);

			node1->RemoveAttribute(attribute);
			node2->AddAttribute(attribute);
		}
	}

	void testSerialize() {

	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(NodeTest);
