#include <system/factory/module.h>
#include "isource.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class Source : public ISource {
	public:
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = (IParam*)this;
				AddRef();
			}
			else if (type == IID_ISource) {
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

		//	ISource
		const Core::String GetId() const override {
			return m_id;
		}
		
		void SetId(const Core::String& value) override {
			m_id = value;
		}

		const Core::String GetName() const override {
			return m_name;
		}
		
		void SetName(const Core::String& value) override {
			m_name = value;
		}
		
		void SetAccessor(IAccessorPtr value) override {
			m_accessor = value;
		}
		
		IAccessorPtr GetAccessor() override {
			return m_accessor;
		}
		
		const IAccessorPtr GetAccessor() const override {
			return m_accessor;
		}

		IArrayPtr GetArray() override {
			return m_array;
		}

		const IArrayPtr GetArray() const override {
			return m_array;
		}

		void SetArray(IArrayPtr value) override {
			m_array = value;
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_id;
		Core::String m_name;
		IAccessorPtr m_accessor{ nullptr };
		IArrayPtr m_array{ nullptr };
	};

	PUNK_REGISTER_CREATOR(CLSID_Source, (System::CreateInstance<Source, ISource>));
}
PUNK_ENGINE_END