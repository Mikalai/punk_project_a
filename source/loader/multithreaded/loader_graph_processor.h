#ifndef LOADER_GRAPH_PROCESSOR_H
#define LOADER_GRAPH_PROCESSOR_H

#include <map>
#include <list>
#include <config.h>
#include <atomic>
#include <scene/module.h>
#include <system/logger/module.h>
#include "async_parser.h"
#include <scene/command.h>
#include "loader_commands.h"
#include "iloader_processor.h"

PUNK_ENGINE_BEGIN
namespace Scene {
	class CommandBase;
}
namespace Loader {
    class LoaderCache;    	

	class PUNK_ENGINE_LOCAL LoaderGraphProcessor : public ILoaderProcessor
    {
    public:
        LoaderGraphProcessor();
		virtual ~LoaderGraphProcessor();
		void BeginPreProcessSync() override;
		void PreProcess() override;
		void EndPreProcessSync() override;
		void BeginPostProcessSync() override;
		void PostProcess() override;
		void EndPostProcessSync() override;
		void InternalProcess() override;
		void SendAsyncCommand(Scene::CommandBase* cmd) override;
		void SendSyncCommand(Scene::CommandBase* cmd) override;
		void WaitComplete() override;
		void Terminate() override;

	private:

		void ProcessCommand(Scene::CommandBase* cmd);
		void ProcessLoaderDomainCommands(Scene::CommandBase* cmd);
		void ProcessSceneDomainCommands(Scene::CommandBase* cmd);

		void ProcessLoaderAddCommand(CmdAdd* cmd);
		void ProcessLoaderRemoveCommand(CmdRemove* cmd);
		void ProcessLoaderNodeAddedCommand(CmdNodeAdded* cmd);
		void ProcessLoaderNodeRemovedCommand(CmdNodeRemoved* cmd);
		void ProcessLoaderAddLoadedObjectCommand(CmdAddLoadedObject* cmd);
		void ProcessLoaderSetNewGraphCommand(CmdSetGraph* cmd);
		void ProcessLoaderLoadFileCommand(CmdLoadFile* cmd);

		
		void ProcessSceneSetManagerCommand(Scene::CmdSceneSetManager* cmd);

		void FlushCommands();
	private:
		System::ThreadMutex m_process_mutex;
		Scene::ISceneManager* m_scene_manager{ nullptr };
		System::ThreadMutex m_sync_thread;
		std::vector<Scene::CommandBase*> m_sync_commands;
		System::ThreadMutex m_async_thread;
		std::vector<Scene::CommandBase*> m_async_commands;

		void SetGraph(Scene::ISceneGraph* graph) ;
		const Core::String GetName() const ;
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
        void AddLoadedObject(Scene::INode* node, Core::IObject* o);

		void OnStartProcessing() ;
		void OnInternalUpdate(Scene::CommandBase* task) ;
		void OnPreUpdate(Scene::CommandBase* command) ;
		void OnPostUpdate(Scene::CommandBase* command);
		void OnWaitProcessingComplete() ;

		void OnCmdAddLoadedObject(CmdAddLoadedObject* add_loaded_object);
	private:
		System::ILogger* m_logger{ System::GetDefaultLogger() };
    };
}
PUNK_ENGINE_END

#endif // LOADER_GRAPH_PROCESSOR_H
