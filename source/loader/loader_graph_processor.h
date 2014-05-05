#ifndef LOADER_GRAPH_PROCESSOR_H
#define LOADER_GRAPH_PROCESSOR_H

#include <map>
#include <list>
#include <config.h>
#include <atomic>
#include <scene/module.h>
#include <system/logger/module.h>
#include "async_parser.h"
#include "loader_commands.h"

PUNK_ENGINE_BEGIN
namespace Loader {
    class LoaderCache;    

    class PUNK_ENGINE_API LoaderGraphProcessor : public Scene::GraphProcessorBase
    {
    public:
        LoaderGraphProcessor();
               
		void SetGraph(Scene::ISceneGraph* graph) override;
		const Core::String GetName() const override;
		bool Process(Scene::INode* node, bool (LoaderGraphProcessor::*func)(Scene::INode*));
        void LoadCompleted(AsyncParserTask* task);

        bool Delete(Scene::INode* node);
        bool OnNodeAdded(Scene::INode* child);
        bool OnNodeRemoved(Scene::INode* child);

        void AddChild(Scene::INode* parent, Scene::INode* child);
        void RemoveChild(Scene::INode* parent, Scene::INode* child);
        void ChildAdded(Scene::INode* parent, Scene::INode* child);
        void ChildRemoved(Scene::INode* parent, Scene::INode* child);

        void LoadFile(Scene::INode* node, const Core::String& filename);
        void AddLoadedObject(Scene::INode* node, Core::Object* o);

	protected:
		void OnStartProcessing() override;
		void OnInternalUpdate(Scene::CommandBase* task) override;
		void OnPreUpdate(Scene::CommandBase* command) override;
		void OnPostUpdate(Scene::CommandBase* command) override;
		void OnWaitProcessingComplete() override;

	private:
		System::ILogger* m_logger{ System::GetDefaultLogger() };
    };
}
PUNK_ENGINE_END

#endif // LOADER_GRAPH_PROCESSOR_H
