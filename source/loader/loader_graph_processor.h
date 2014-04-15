#ifndef LOADER_GRAPH_PROCESSOR_H
#define LOADER_GRAPH_PROCESSOR_H

#include <map>
#include <list>
#include <config.h>
#include <atomic>
#include <scene/module.h>
#include "async_parser.h"

PUNK_ENGINE_BEGIN
namespace Loader {
    class LoaderCache;

    enum class LoaderCommands {
        Add,
        Remove,
        NodeAdded,
        NodeRemoved,
        AddLoadedObject,
        SetNewGraph
    };

    struct LoaderAddCommand {
        Scene::INode* parent;
        Scene::INode* child;
    };

    struct LoaderRemoveCommand {
        Scene::INode* parent;
        Scene::INode* child;
    };

    struct LoaderNodeAddedCommand {
        Scene::INode* parent;
        Scene::INode* new_node;
    };

    struct LoaderNodeRemovedCommand {
        Scene::INode* parent;
        Scene::INode* old_node;
    };

    struct LoaderAddLoadedObjectCommand {
        Scene::INode* node;
        Core::Object* object;
    };

    struct LoaderSetGraphCommand {
        Scene::ISceneGraph* new_graph;
    };

    //
    //  Command is anything that someone can call from other threads
    //
    struct LoaderCommand {
        LoaderCommands command;
        union {
            LoaderAddCommand add;
            LoaderRemoveCommand remove;
            LoaderNodeAddedCommand node_added;
            LoaderNodeRemovedCommand node_removed;
            LoaderAddLoadedObjectCommand add_loaded_object;
            LoaderSetGraphCommand set_graph;
        };
    };

    enum class LoaderTasks {
        Load
    };

    struct LoadFileTask {
        Scene::INode* node;
        wchar_t filename[MAX_PATH];
    };

    //
    //  Task is anything that should be processed in the internal thread of the processor
    //
    struct LoaderTask {
        LoaderTasks task;
        union {
            LoadFileTask load_file;
        };
    };

    class PUNK_ENGINE_API LoaderGraphProcessor : public Scene::IGraphProcessor
    {
    public:
        LoaderGraphProcessor();
        void SetGraph(Scene::ISceneGraph* graph) override;
        void BeginUpdate(int dt) override;
        void FinishUpdate() override;
        void WaitUpdateStart() override;
        void WaitUpdateFinish() override;
        void StopProcessing() override;
        void WaitProcessingComplete() override;

        void PreUpdate();
        void PostUpdate();
        bool Process(Scene::INode* node, bool (LoaderGraphProcessor::*func)(Scene::INode*));
        void InternalUpdate();
        bool IsFinish();
        void WaitUpdate();
        void EndUpdate();
        Scene::ISceneGraph* GetSceneGraph() const;

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

        void AddCommand(LoaderCommand& cmd);
        void AddTask(LoaderTask& task);

    public:
        bool m_delete {false};
        int m_last_update_step;
        Scene::ISceneGraph* m_graph {nullptr};

        System::ThreadMutex m_commands_mutex;
        std::vector<LoaderCommand> m_commands;

        System::ThreadMutex m_tasks_mutex;
        std::vector<LoaderTask> m_tasks;

        System::ThreadMutex m_allow_update;
        System::Thread m_thread;
    };
}
PUNK_ENGINE_END

#endif // LOADER_GRAPH_PROCESSOR_H
