#include <system/factory/module.h>
#include "iscene_module.h"

PUNK_ENGINE_BEGIN
namespace SceneModule {

	class SceneModuleImpl : public ISceneModule {
	public:

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, System::IID_IModule, IID_ISceneModule });
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
			return "Scene";
		}

		const Core::String GetDescription() const {
			return "Perform scene managment and data storage";
		}

		const Core::String GetFullpath() const {
			return m_fullpath;
		}

		void SetFullpath(const Core::String& value) {
			m_fullpath = value;
		}


		//	ISceneModule
		Core::Pointer<ISceneManager> GetSceneManager() override {
			if (!m_scene_manager) {
				m_scene_manager = System::CreateInstancePtr<ISceneManager>(CLSID_SceneManager, IID_ISceneManager);
			}
			return m_scene_manager;
		}

	private:
		std::atomic<std::uint32_t> m_ref_count;
		Core::String m_fullpath;
		Core::Pointer<ISceneManager> m_scene_manager{ nullptr, Core::DestroyObject };
	};

	SceneModuleImpl g_scene_module;

	extern "C" PUNK_ENGINE_API System::IModule* GetPunkModule() {
		return &g_scene_module;
	}
}
PUNK_ENGINE_END
