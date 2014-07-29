#include <system/factory/module.h>
#include "irender_module.h"

PUNK_ENGINE_BEGIN
namespace LowLevelRender {

	class RenderModule : public IRenderModule {
	public:

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, System::IID_IModule, IID_IRenderModule});
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v)
				delete this;
			return v;
		}

		//	IRenderModule
		void Create(const Core::Guid& clsid, const Core::Guid& iid, void** object) override {
			System::CreateInstance(clsid, iid, object);
		}

		const Core::String GetName() const override {
			return "Render";
		}

		const Core::String GetDescription() const {
			return "Perform high level render operations";
		}

		const Core::String GetFullpath() const {
			return m_fullpath;
		}

		void SetFullpath(const Core::String& value) {
			m_fullpath = value;
		}


		//	IRenderModule		

	private:
		std::atomic<std::uint32_t> m_ref_count;
		Core::String m_fullpath;
	};

	RenderModule g_render_module;

	extern "C" PUNK_ENGINE_API System::IModule* GetPunkModule() {
		return &g_render_module;
	}
}
PUNK_ENGINE_END
