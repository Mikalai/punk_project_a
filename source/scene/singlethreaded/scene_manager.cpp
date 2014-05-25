#include <core/ifactory.h>
#include <system/errors/module.h>
#include "scene_manager.h"

PUNK_ENGINE_BEGIN
namespace SceneModule {

	SceneManager::SceneManager() {
		m_factory->CreateInstance(IID_IScene, (void**)m_scene);
	}

	SceneManager::~SceneManager() {
		m_scene->Release();
	}	

	void SceneManager::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_ISceneManager });
	}

	IScene* SceneManager::GetScene() {
		return m_scene;
	}

	void CreateSceneManager(void** object) {
		if (!object)
			return;
	}

	PUNK_REGISTER_CREATOR(IID_ISceneManager, Core::CreateInstance<SceneManager>);
}
PUNK_ENGINE_END
