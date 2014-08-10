#include <system/factory/module.h>
#include "iattributes_manager.h"
#include "iattributes_module.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class AttributeMdoule : public IAttributesModule {
	public:

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, System::IID_IModule, IID_IAttributesModule });
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

		//	IModule
		void Create(const Core::Guid& clsid, const Core::Guid& iid, void** object) override {
			System::CreateInstance(clsid, iid, object);
		}

		const Core::String GetName() const override {
			return "Attributes";
		}

		const Core::String GetDescription() const {
			return "Basic elements that can be added into the world";
		}

		const Core::String GetFullpath() const {
			return m_fullpath;
		}

		void SetFullpath(const Core::String& value) {
			m_fullpath = value;
		}


		//	IAttributesModule
		virtual Core::Pointer<IAttributesManager> GetAttributeManager() override {
			if (!m_attribute_manager) {
				m_attribute_manager = System::CreateInstancePtr<IAttributesManager>(CLSID_AttributesManager, IID_IAttributesManager);
			}
			return m_attribute_manager;
		}

	private:
		std::atomic<std::uint32_t> m_ref_count;
		Core::String m_fullpath;
		Core::Pointer<IAttributesManager> m_attribute_manager{ nullptr, Core::DestroyObject };
	};

	Core::Pointer<AttributeMdoule> g_scene_module{ nullptr, Core::DestroyObject };

	extern "C" PUNK_ENGINE_API System::IModule* GetPunkModule() {
		if (!g_scene_module) {
			g_scene_module.reset(new AttributeMdoule);
		}
		return g_scene_module.get();
	}
}
PUNK_ENGINE_END
