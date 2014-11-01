#ifndef _H_META_CLASS
#define _H_META_CLASS

#include <iostream>
#include <map>
#include <tuple>
#include <core/action.h>
#include <system/logger/module.h>

using namespace Punk::Engine;


class IMetaInterface : public Core::IObject {
public:
	virtual void Invoke(const Core::String& method, Core::Buffer& args) = 0;
};

class MetaClassBase {

};

template<class T, typename ... Args>
using MetaMethod = std::tuple < std::string, void (T::*)(Args...) > ;

template<class T>
class MetaClass : public MetaClassBase {
public:
	
	MetaClass()
	{}

	template<typename ... Args>
	void Invoke(T* o, const std::string& method, Args... args) {
		auto aa = m_methods[method];
		if (aa == nullptr) {
			System::GetDefaultLogger()->Error(Core::String("Can't find method ") + method.c_str());
			return;
		}
		auto a = dynamic_cast<Core::Action<T, Args...>*>(aa);
		if (!a) {
			System::GetDefaultLogger()->Error(Core::String("Can't cast method ") + method.c_str());
			return;
		}

		(*a)(o, args...);
	}

	template < typename ... Args >
	void AddMetaMethod(const std::string& name, void(T::*method)(Args...)) {
		auto action = new Core::Action < T, Args... > { nullptr, method };
		m_methods[name] = action;
	}
		
	std::map<std::string, Core::MetaAction*> m_methods; 
};

class RegisterTestClass; 
class TestClass {

public:

	void Method() {
		std::cout << "Method" << std::endl;
	}

	void Method2(int value) {
		std::cout << "Method2 " << value << std::endl;
	}

	void Method3(int& k) {
		k = 15;		
	}

	void Method4(int* k) {
		*k = 15;
	}

	MetaClass<TestClass>* GetType() {
		return meta_class;
	}

private:
	friend class RegisterTestClass;
	static MetaClass < TestClass >* meta_class;
};


#endif	//	_H_META_CLASS