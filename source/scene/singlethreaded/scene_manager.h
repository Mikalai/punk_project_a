#ifndef _H_SCENE_MANAGER
#define _H_SCENE_MANAGER

#include <config.h>
#include <map>
#include <core/ifactory.h>
#include <system/logger/module.h>
#include "iscene_manager.h"
#include "iscene.h"

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
	private:
		std::vector<IProcessor*> m_processors;
        Core::UniquePtr<IScene> m_scene{ nullptr, Core::DestroyObject };
		System::ILogger* m_logger{ System::GetDefaultLogger() };		

		PUNK_OBJECT_DEFAULT_IMPL(SceneManager);
	};

}
PUNK_ENGINE_END

#endif	//	_H_SCENE_MANAGER
