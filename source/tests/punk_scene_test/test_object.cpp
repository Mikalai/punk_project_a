#include <core/iserializable.h>
#include <system/factory/module.h>
#include <string/module.h>
#include "test_object.h"

using namespace Punk::Engine;

class TestObjectClass : public ITestObjectInterface, public Core::ISerializable {
public:
	//	IObject
	void QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;

		*object = nullptr;

		if (type == Core::IID_IObject) {
			*object = (ITestObjectInterface*)this;
			AddRef();
			return;
		}
		else if (type == Core::IID_ISerializable) {
			*object = (ISerializable*)this;
			AddRef();
			return;
		}
		else if (type == IID_ITestObjectInterface) {
			*object = (ITestObjectInterface*)this;
			AddRef();
			return;
		}
	}
	std::uint32_t AddRef() override {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t Release() override {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v) {
			delete this;
		}
		return v;
	}

	//	ISerializable
	void Serialize(Core::Buffer& buffer) override {
		buffer.WritePod(CLSID_TestObject);
		buffer.WritePod(m_data);
	}

	void Deserialize(Core::Buffer& buffer) override {
		buffer.ReadPod(m_data);
	}

	//	ITestObjectInterface
	void Set(int value) override {
		m_data = value;
	}

	int Get() override {
		return m_data;
	}

	std::atomic<std::uint32_t> m_ref_count{ 0 };
	int m_data{ 0 };
};

PUNK_REGISTER_CREATOR(CLSID_TestObject, (System::CreateInstance<TestObjectClass, ITestObjectInterface>));