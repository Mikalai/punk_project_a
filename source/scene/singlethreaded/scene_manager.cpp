#include <system/factory/module.h>
#include <system/errors/module.h>
#include "iprocessor.h"
#include "scene_manager.h"

PUNK_ENGINE_BEGIN
namespace SceneModule {

	SceneManager::SceneManager() {
        LOG_FUNCTION_SCOPE
        m_scene = System::CreateInstancePtr<IScene>(IID_IScene);
	}

	SceneManager::~SceneManager() {
        LOG_FUNCTION_SCOPE
		while (!m_processors.empty()) {
			m_processors.back()->Release();
			m_processors.pop_back();
		}		
	}	

	void SceneManager::QueryInterface(const Core::Guid& type, void** object) {
        LOG_FUNCTION_SCOPE
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_ISceneManager });
	}

	IScene* SceneManager::GetScene() {
        LOG_FUNCTION_SCOPE
        return m_scene.get();
	}

	void CreateSceneManager(void** object) {
        LOG_FUNCTION_SCOPE
		if (!object)
			return;
	}

	void SceneManager::AddProcessor(IProcessor* processor) {
        LOG_FUNCTION_SCOPE
		processor->AddRef();
		m_processors.push_back(processor);
		processor->SetSceneManager(this);
	}

	void SceneManager::Update(float dt) {
        LOG_FUNCTION_SCOPE
		for (auto i : m_processors){
			i->Update(dt);
		}
	}

    PUNK_REGISTER_CREATOR(IID_ISceneManager, (System::CreateInstance<SceneManager, ISceneManager>));
}
PUNK_ENGINE_END
