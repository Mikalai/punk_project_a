#include "test_class.h"

class RegisterTestClass {
public:
	RegisterTestClass() {
		TestClass::meta_class = new MetaClass < TestClass > ;
		TestClass::meta_class->AddMetaMethod("Method", &TestClass::Method);
		TestClass::meta_class->AddMetaMethod("Method2", &TestClass::Method2);
		TestClass::meta_class->AddMetaMethod("Method3", &TestClass::Method3);
		TestClass::meta_class->AddMetaMethod("Method4", &TestClass::Method4);
	}
	~RegisterTestClass() {
		delete TestClass::meta_class;
		TestClass::meta_class = nullptr;
	}
};

MetaClass<TestClass>* TestClass::meta_class;

static RegisterTestClass test_class;