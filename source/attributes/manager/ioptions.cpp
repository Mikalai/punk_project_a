#include <system/factory/ifactory.h>
#include <core/iobject_impl.h>
#include "ioptions.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class PUNK_ENGINE_LOCAL Options : public IOptions {
	public:

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IOptions });
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

		//	IOptions
		virtual const Core::String& GetDataPath() const {
			return m_data_path;
		}

		virtual void SetDataPath(const Core::String& value) {
			m_data_path = value;
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_data_path;		
	};

	PUNK_REGISTER_CREATOR(CLSID_Options, (System::CreateInstance<Options, IOptions>));
}
PUNK_ENGINE_END
