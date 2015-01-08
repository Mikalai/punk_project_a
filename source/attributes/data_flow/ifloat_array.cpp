#include <core/iserializable.h>
#include <system/factory/module.h>
#include "ifloat_array.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class FloatArray : public IFloatArray, public Core::ISerializable {
	public:
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = (IFloatArray*)this;
				AddRef();
			}
			else if (type == Core::IID_ISerializable) {
				*object = (Core::ISerializable*)this;
				AddRef();
			}
			else if (type == IID_IFloatArray) {
				*object = this;
				AddRef();
			}
			else if (type == IID_IArray) {
				*object = this;
				AddRef();
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

		//	IArray
		std::uint32_t GetCount() const override {
			return (std::uint32_t)m_data.size();
		}

		void SetCount(std::uint32_t value) override {
			m_data.resize(value);
		}

		const Core::String GetId() override {
			return m_id;
		}

		void SetId(const Core::String& value) override {
			m_id = value;
		}

		const Core::String GetName() override {
			return m_name;
		}

		void SetName(const Core::String& value) override {
			m_name = value;
		}		

		void* Data() {
			return (void*)m_data.data();
		}

		const void* Data() const override {
			return (const void*)m_data.data();
		}

		//	IFloatArray
		void SetValue(int index, float value) override {
			m_data.at(index) = value;
		}

		float GetValue(int index) const override {
			return m_data.at(index);
		}

		//	ISerializable
		void Serialize(Core::Buffer& buffer) override {
			throw System::Error::NotImplemented{ "Serialize not implemented", 0 };
		}

		void Deserialize(Core::Buffer& buffer) override {
			throw System::Error::NotImplemented{ "Deserialize is not implemented", 0 };
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_id;
		Core::String m_name;
		std::vector<float> m_data;
	};

	PUNK_REGISTER_CREATOR(CLSID_FloatArray, (System::CreateInstance<FloatArray, IFloatArray>));
}
PUNK_ENGINE_END
