#ifndef LOADER_GRAPH_PROCESSOR_H
#define LOADER_GRAPH_PROCESSOR_H

#include <map>
#include <list>
#include <config.h>
#include <atomic>
#include <scene/singlethreaded/module.h>
#include <system/logger/module.h>
#include <attributes/module.h>
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
        //  IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
        std::uint32_t AddRef() override;
        std::uint32_t Release() override;
		void SetScene(SceneModule::IScene* value) override;
		void OnNodeAdded(Core::Pointer<SceneModule::INode> parent, Core::Pointer<SceneModule::INode> child) override;
		void OnNodeRemoved(Core::Pointer<SceneModule::INode> parent, Core::Pointer<SceneModule::INode> child) override;
		void OnAttributeAdded(Core::Pointer<SceneModule::INode> node, Core::Pointer<SceneModule::IAttribute> attribute) override;
		void OnAttributeUpdated(Core::Pointer<SceneModule::INode> node, Core::Pointer<SceneModule::IAttribute> old_attribute, Core::Pointer<SceneModule::IAttribute> new_attribute) override;
		void OnAttributeRemoved(Core::Pointer<SceneModule::INode> node, Core::Pointer<SceneModule::IAttribute> attribute) override;

	private:
		void ProcessNode(Core::Pointer<SceneModule::INode> node);		
		Core::Pointer<Core::IObject> GetFileData(const Core::String& filename);

	private:
        std::atomic<std::uint32_t> m_ref_count;
		Core::Pointer<Attributes::IOptions> m_options{ nullptr, Core::DestroyObject };
		System::ILogger* m_logger{ System::GetDefaultLogger() };
		SceneModule::IScene* m_scene{ nullptr };		
		Core::ObjectPool<Core::String, Core::IObject> m_loaded_stuff;		
    };
}
PUNK_ENGINE_END

#endif // LOADER_GRAPH_PROCESSOR_H
