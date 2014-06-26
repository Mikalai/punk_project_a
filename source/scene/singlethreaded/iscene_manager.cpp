#include <system/factory/module.h>
#include <system/errors/module.h>
#include <config.h>
#include <map>
#include <system/factory/module.h>
#include <system/logger/module.h>
#include "iscene_manager.h"
#include "iscene.h"
#include "iprocessor.h"
#include "iscene_manager.h"

PUNK_ENGINE_BEGIN
namespace SceneModule {


	class PUNK_ENGINE_LOCAL SceneManager : public ISceneManager {
	public:
		SceneManager();
		virtual ~SceneManager();
		void QueryInterface(const Core::Guid& type, void** object) override;
		IScene* GetScene() override;
		void AddProcessor(IProcessor* processor) override;
		void Update(float dt) override;
		void Terminate() override;
		bool IsTerminated() const override;
	private:
		void TerminateProcessors();
	
	private:
		std::vector<IProcessor*> m_processors;
		Core::Pointer<IScene> m_scene{ nullptr, Core::DestroyObject };
		System::ILogger* m_logger{ System::GetDefaultLogger() };
		bool m_is_terminated{ false };
		bool m_need_terminate{ false };
		PUNK_OBJECT_DEFAULT_IMPL(SceneManager);
	};


	SceneManager::SceneManager() {
		LOG_FUNCTION_SCOPE;
		m_scene = System::CreateInstancePtr<IScene>(IID_IScene);
	}

	SceneManager::~SceneManager() {
		LOG_FUNCTION_SCOPE;
		while (!m_processors.empty()) {
			m_processors.back()->Release();
			m_processors.pop_back();
		}
	}

	void SceneManager::TerminateProcessors() {
		for (auto processor : m_processors) {
			processor->Terminate();
		}
		m_need_terminate = false;
		m_is_terminated = true;
	}

	void SceneManager::Terminate() {		
		m_need_terminate = true;
	}

	bool SceneManager::IsTerminated() const {
		return m_is_terminated;
	}

	void SceneManager::QueryInterface(const Core::Guid& type, void** object) {
		LOG_FUNCTION_SCOPE;
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_ISceneManager });
	}

	IScene* SceneManager::GetScene() {
		LOG_FUNCTION_SCOPE;
		return m_scene.get();
	}

	void CreateSceneManager(void** object) {
		LOG_FUNCTION_SCOPE;
		if (!object)
			return;
	}

	void SceneManager::AddProcessor(IProcessor* processor) {
		LOG_FUNCTION_SCOPE;
		processor->AddRef();
		m_processors.push_back(processor);
		processor->SetSceneManager(this);
	}

	void SceneManager::Update(float dt) {
		LOG_FUNCTION_SCOPE;

		if (m_need_terminate) {
			TerminateProcessors();
		}

		if (!m_is_terminated) {
			for (auto i : m_processors){
				i->Update(dt);
			}
		}
	}

	PUNK_REGISTER_CREATOR(IID_ISceneManager, (System::CreateInstance<SceneManager, ISceneManager>));
}
PUNK_ENGINE_END
