#include <core/ifactory.h>
#include <system/errors/module.h>
#include "iprocessor.h"
#include "scene_manager.h"

PUNK_ENGINE_BEGIN
namespace SceneModule {

	DEFINE_PUNK_GUID(IID_ISceneManager, "D8138AD5-F05C-4209-83CF-A21697E0547A");

	SceneManager::SceneManager() {
		m_factory->CreateInstance(IID_IScene, (void**)&m_scene);
	}

	SceneManager::~SceneManager() {
		while (!m_processors.empty()) {
			m_processors.back()->Release();
			m_processors.pop_back();
		}
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

	void SceneManager::AddProcessor(IProcessor* processor) {
		processor->AddRef();
		m_processors.push_back(processor);
		processor->SetSceneManager(this);
	}

	void SceneManager::Update(float dt) {
		for (auto i : m_processors){
			i->Update(dt);
		}
	}

	PUNK_REGISTER_CREATOR(IID_ISceneManager, (Core::CreateInstance<SceneManager, ISceneManager>));
}
PUNK_ENGINE_END
