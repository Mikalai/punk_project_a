#ifndef LOADER_GRAPH_PROCESSOR_H
#define LOADER_GRAPH_PROCESSOR_H

#include <map>
#include <list>
#include <config.h>
#include <atomic>
#include <scene/singlethreaded/module.h>
#include <system/logger/module.h>
#include <core/module.h>
#include "async_parser.h"
#include "iio_observer.h"

PUNK_ENGINE_BEGIN
namespace SceneModule {
	class CommandBase;
}
namespace IoModule {
    class LoaderCache;    		

	class PUNK_ENGINE_LOCAL IoObserver : public IIoObserver
    {
    public:
        IoObserver();
		virtual ~IoObserver();
		void QueryInterface(const Core::Guid& type, void** object) override;
		void SetScene(SceneModule::IScene* value) override;
		void OnNodeAdded(SceneModule::INode* parent, SceneModule::INode* child) override;
		void OnNodeRemoved(SceneModule::INode* parent, SceneModule::INode* child) override;
		void OnAttributeAdded(SceneModule::INode* node, SceneModule::IAttribute* attribute) override;
		void OnAttributeUpdated(SceneModule::INode* node, SceneModule::IAttribute* old_attribute, SceneModule::IAttribute* new_attribute) override;
		void OnAttributeRemoved(SceneModule::INode* node, SceneModule::IAttribute* attribute) override;

	private:
		void ProcessNode(SceneModule::INode* node);

	private:
		System::ILogger* m_logger{ System::GetDefaultLogger() };
		SceneModule::IScene* m_scene{ nullptr };
		Core::ObjectPool<Core::String, Core::UniquePtr<Core::IObject>> m_loaded_stuff;
		PUNK_OBJECT_DEFAULT_IMPL(IoObserver);
    };
}
PUNK_ENGINE_END

#endif // LOADER_GRAPH_PROCESSOR_H
