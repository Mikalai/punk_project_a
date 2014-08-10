#ifndef _H_TEST_OBJECT
#define _H_TEST_OBJECT

#include <core/iobject.h>
#include <scene/module.h>

using namespace Punk::Engine;

DECLARE_PUNK_GUID(IID_ITestObjectInterface, "300D03D4-25B4-4B03-8973-C92694510A67");
DECLARE_PUNK_GUID(CLSID_TestObject, "DA518215-FCF9-4E52-99B9-9F8C286663F3");

class ITestObjectInterface : public Core::IObject {
public:
	virtual void Set(int value) = 0;
	virtual int Get() = 0;
};

inline Core::Pointer<SceneModule::INode> CreateNode() {
	auto node = System::CreateInstancePtr<SceneModule::INode>(SceneModule::CLSID_Node, SceneModule::IID_INode);
	return node;
}

inline Core::Pointer<SceneModule::IAttribute> CreateAttribute() {
	auto attribute = System::CreateInstancePtr<SceneModule::IAttribute>(SceneModule::CLSID_Attribute, SceneModule::IID_IAttribute);
	return attribute;
}

inline Core::Pointer<ITestObjectInterface> CreateObject() {
	auto o = System::CreateInstancePtr<ITestObjectInterface>(CLSID_TestObject, IID_ITestObjectInterface);
	return o;
}

#endif	//	_H_TEST_OBJECT