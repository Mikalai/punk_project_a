#include <system/factory/module.h>
#include "ioptics.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class Optics : public IOptics {
	public:
		virtual ~Optics() {

		}

		// IObject		
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = (IOptics*)this;
				AddRef();
			}
			else if (type == IID_IOptics) {
				*object = (IOptics*)this;
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

		//	iOptics
		void SetProjection(IProjectionPtr value) override {
			m_projection = value;
		}

		IProjectionPtr GetProjection() const override {
			return m_projection;
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		IProjectionPtr m_projection;
	};

	PUNK_REGISTER_CREATOR(CLSID_Optics, (System::CreateInstance<Optics, IOptics>));
}
PUNK_ENGINE_END
