#ifndef _H_SCENE_MANAGER
#define _H_SCENE_MANAGER

#include <config.h>
#include <map>
#include <core/ifactory.h>
#include <system/logger/module.h>
#include "iscene_manager.h"
#include "iscene_processor.h"
#include "iscene_worker.h"

PUNK_ENGINE_BEGIN
namespace Scene {
	
	class PUNK_ENGINE_LOCAL SceneManager : public ISceneManager {
	public:
		virtual ~SceneManager();
		virtual void AddProcessor(ISceneProcessor* value) = 0;
		virtual void RemoveProcessor(ISceneProcessor* value) = 0;
		virtual void Start() = 0;
		virtual void Stop() = 0;
	private:
		std::map<ISceneProcessor*, ISceneWorker*> m_workers;
		System::ILogger* m_logger{ System::GetDefaultLogger() };
		Core::IFactory* m_factory{ Core::GetFactory() };
	};

}
PUNK_ENGINE_END

#endif	//	_H_SCENE_MANAGER