#include <system/errors/module.h>
#include "scene_manager.h"

PUNK_ENGINE_BEGIN
namespace Scene {

	SceneManager::~SceneManager() {
		for (auto it = m_workers.begin(); it != m_workers.end(); ++it) {
			it->second->Release();
			it->first->Release();
		}
		m_workers.clear();
	}

	void SceneManager::AddProcessor(ISceneProcessor* value) {		
		auto it = m_workers.find(value);
		if (it != m_workers.end()) {
			m_logger->Warning("ISceneProcessor already added in scene manager");
			return;
		}

		ISceneWorker* worker = nullptr;
		m_factory->CreateInstance(IID_ISceneWorker, (void**)&worker);
		worker->SetProcessor(value);
		value->AddRef();
		m_workers[value] = worker;
	}

	void SceneManager::RemoveProcessor(ISceneProcessor* value) {
		auto it = m_workers.find(value);
		if (it == m_workers.end()) {
			m_logger->Warning("ISceneProcessor was not added to the scene manager");
			return;
		}

		it->first->Release();
		it->second->Release();
		m_workers.erase(it);
	}

}
PUNK_ENGINE_END
