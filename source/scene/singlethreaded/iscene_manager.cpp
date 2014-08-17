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
		SceneManager() {
			LOG_FUNCTION_SCOPE();
		}

		~SceneManager() {
			LOG_FUNCTION_SCOPE();
			while (!m_processors.empty()) {
				m_processors.back()->Release();
				m_processors.pop_back();
			}
		}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			LOG_FUNCTION_SCOPE();
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_ISceneManager });
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

		//	ISceneManager
		void TerminateProcessors() {
			for (auto processor : m_processors) {
				processor->Terminate();
			}
			m_need_terminate = false;
			m_is_terminated = true;
		}

		void Terminate() {
			m_need_terminate = true;
		}

		bool IsTerminated() const {
			return m_is_terminated;
		}		

		Core::Pointer<IScene> GetCurrentScene() override {
			LOG_FUNCTION_SCOPE();
			return m_current_scene;
		}

		void SetCurrentScene(Core::Pointer<IScene> scene) override {
			m_current_scene = scene;
		}

		void AddScene(Core::Pointer<IScene> scene) override {
			m_scenes.push_back(scene);
		}

		std::uint32_t GetScenesCount() const override {
			return m_scenes.size();
		}

		Core::Pointer<IScene> GetScene(std::uint32_t index) {
			return m_scenes[index];
		}

		std::uint32_t GetSceneIndex(Core::Pointer<IScene> scene) {
			for (std::uint32_t i = 0, max_i = (std::uint32_t)m_scenes.size(); i < max_i;  ++i) {
				if (m_scenes[i] == scene)
					return i;
			}
			return -1;
		}

		void RemoveScene(std::uint32_t index) override {
			m_scenes.erase(m_scenes.begin() + index);
		}

		void RemoveAllScenes() override {
			m_scenes.clear();
			m_current_scene.reset(nullptr);
		}

		void AddProcessor(Core::Pointer<IProcessor> processor) override {
			LOG_FUNCTION_SCOPE();
			m_processors.push_back(processor);
			processor->SetSceneManager(this);
		}

		void Update(float dt) override {
			LOG_FUNCTION_SCOPE();

			if (m_need_terminate) {
				TerminateProcessors();
			}

			if (!m_is_terminated) {
				for (auto i : m_processors){
					i->Update(dt);
				}
			}
		}
	
	private:

		std::atomic<std::uint32_t> m_ref_count{ 0 };
		std::vector<Core::Pointer<IProcessor>> m_processors;
		Core::Pointer<IScene> m_current_scene{ nullptr, Core::DestroyObject };
		std::vector<Core::Pointer<IScene>> m_scenes;
		System::ILogger* m_logger{ System::GetDefaultLogger() };
		bool m_is_terminated{ false };
		bool m_need_terminate{ false };		
	};

	PUNK_REGISTER_CREATOR(CLSID_SceneManager, (System::CreateInstance<SceneManager, ISceneManager>));
}
PUNK_ENGINE_END
