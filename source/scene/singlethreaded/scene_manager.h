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
	private:
		IScene* m_scene{ nullptr };
		System::ILogger* m_logger{ System::GetDefaultLogger() };
		Core::IFactory* m_factory{ Core::GetFactory() };

		PUNK_OBJECT_DEFAULT_IMPL(SceneManager);
	};

}
PUNK_ENGINE_END

#endif	//	_H_SCENE_MANAGER