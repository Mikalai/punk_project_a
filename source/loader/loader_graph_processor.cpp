#include <core/object.h>
#include <loader/parser/parse_punk_file.h>
#include "loader_cache.h"
#include "loader_graph_processor.h"
#include "async_parser.h"

PUNK_ENGINE_BEGIN
namespace Loader {

    class LoaderWorkItem : public System::WorkItem {
    public:
        void Run(void *data) override {
            LoaderGraphProcessor* proc = (LoaderGraphProcessor*)data;
            if (!proc)
                return;

            Scene::ISceneGraph* scene = proc->GetSceneGraph();
            while (!proc->IsFinish()) {
                proc->WaitUpdateStart();

				bool process_scene = (scene = proc->GetSceneGraph()) != nullptr;

				if (process_scene) {
					scene->Lock();
					proc->PreUpdate();
					scene->Unlock();
				}


                proc->InternalUpdate();

				if (process_scene) {
					scene->Lock();
					proc->PostUpdate();
					scene->Unlock();
				}

                proc->FinishUpdate();
            }
        }
    };

    LoaderGraphProcessor::LoaderGraphProcessor()
    {
    }

    Scene::ISceneGraph* LoaderGraphProcessor::GetSceneGraph() const {
        return m_graph;
    }

    void LoaderGraphProcessor::StartProcessing() {
        m_thread.Start(new LoaderWorkItem, this);
        m_thread.Resume();
    }

    void LoaderGraphProcessor::WaitUpdateStart() {
        m_allow_update.Lock();
    }

    void LoaderGraphProcessor::WaitUpdateFinish() {
        m_allow_update.Lock();
    }

    void LoaderGraphProcessor::FinishUpdate() {
        m_allow_update.Unlock();
    }

    void LoaderGraphProcessor::BeginUpdate(int dt_ms) {        
        m_last_update_step = dt_ms;
        m_allow_update.Unlock();
    }

    void LoaderGraphProcessor::InternalUpdate()
    {
        m_tasks_mutex.Lock();
        auto tasks = m_tasks;
        m_tasks.clear();
        m_tasks_mutex.Unlock();

        for (LoaderTask task : tasks) {
            if (task.task == LoaderTasks::Load) {
                Core::Object* o = ParsePunkFile(task.load_file.filename);
                auto graph = dynamic_cast<Scene::ISceneGraph*>(o);
				if (graph) {
					auto node = graph->ReleaseRoot();
					AddChild(task.load_file.node, node);
					delete graph;
				}
				else {
					auto node = dynamic_cast<Scene::INode*>(o);
					if (node)
						AddChild(task.load_file.node, node);
					else {
						AddLoadedObject(task.load_file.node, o);
					}
				}
			}
			else if (task.task == LoaderTasks::SetNewGraph) {
				m_graph = task.set_graph.new_graph;
				LoaderCommand cmd;
				cmd.command = LoaderCommands::SetNewGraph;
				cmd.set_graph.new_graph = m_graph;
				AddCommand(cmd);
			}
			
        }
    }

    void LoaderGraphProcessor::PreUpdate() {
        std::stack<Scene::INode*> stack;
        stack.push(m_graph->GetRoot());

        while (!stack.empty()) {
            Scene::INode* node = stack.top();
            stack.pop();
            for (std::uint64_t i = 0; i < node->GetChildrenCount(); ++i)
                stack.push(node->GetChild(i));
        }
    }

    void LoaderGraphProcessor::PostUpdate() {        
        m_commands_mutex.Lock();
        auto commands = m_commands;
        m_commands.clear();
        m_commands_mutex.Unlock();

        for (LoaderCommand cmd : commands) {
            if (cmd.command == LoaderCommands::Add) {
                Scene::INode* parent = cmd.add.parent;
                Scene::INode* child = cmd.add.child;
                parent->AddChild(child);
            }
            else if (cmd.command == LoaderCommands::Remove) {
                Scene::INode* parent = cmd.remove.parent;
                Scene::INode* child = cmd.remove.child;
                parent->RemoveChild(child, true);
            }
            else if (cmd.command == LoaderCommands::NodeAdded) {
                Process(cmd.node_added.new_node, &LoaderGraphProcessor::OnNodeAdded);
            }
            else if (cmd.command == LoaderCommands::NodeRemoved) {
                Process(cmd.node_removed.old_node, &LoaderGraphProcessor::OnNodeRemoved);
            }
            else if (cmd.command == LoaderCommands::AddLoadedObject) {
                Scene::INode* node = cmd.add_loaded_object.node;
                Core::Object* object = cmd.add_loaded_object.object;
                node->Set<Core::Object>(L"Loader.Data", object);
            }
            else if (cmd.command == LoaderCommands::SetNewGraph) {
                m_graph = cmd.set_graph.new_graph;
                m_graph->SubscribeOnNodeAdded(new Core::Action<LoaderGraphProcessor, Scene::INode*, Scene::INode*>(
                                                this, &LoaderGraphProcessor::ChildAdded));
                m_graph->SubscribeOnNodeRemoved(new Core::Action<LoaderGraphProcessor, Scene::INode*, Scene::INode*>(
                                                  this, &LoaderGraphProcessor::ChildRemoved));
				Process(m_graph->GetRoot(), &LoaderGraphProcessor::OnNodeAdded);
            }
        }
    }

    void LoaderGraphProcessor::SetGraph(Scene::ISceneGraph *graph) {		
		LoaderTask task;
		task.task = LoaderTasks::SetNewGraph;
		task.set_graph.new_graph = graph;
		AddTask(task);
    }

    bool LoaderGraphProcessor::Process(Scene::INode *node, bool (LoaderGraphProcessor::*func)(Scene::INode *)) {
        if ((this->*func)(node)) {
            for (std::uint64_t i = 0; i < node->GetChildrenCount(); ++i) {
                if (Process(node->GetChild(i), func))
                    return true;
            }
        }
        return false;
    }

    bool LoaderGraphProcessor::Delete(Scene::INode *node) {
        node->Remove<Core::Object>(L"Loader.Data");
        return false;
    }

    void LoaderGraphProcessor::AddChild(Scene::INode *parent, Scene::INode *child) {
        LoaderCommand command;
        LoaderAddCommand& cmd = command.add;
        cmd.child = child;
        cmd.parent = parent;
        command.command = LoaderCommands::Add;
        AddCommand(command);
    }

    void LoaderGraphProcessor::RemoveChild(Scene::INode *parent, Scene::INode *child) {
        LoaderCommand command;
        LoaderRemoveCommand& cmd = command.remove;
        cmd.child = child;
        cmd.parent = parent;
        command.command = LoaderCommands::Remove;
        AddCommand(command);
    }

    void LoaderGraphProcessor::ChildAdded(Scene::INode *parent, Scene::INode *child) {
        LoaderCommand command;
        LoaderNodeAddedCommand& cmd = command.node_added;
        cmd.parent = parent;
        cmd.new_node = child;
        command.command = LoaderCommands::NodeAdded;
        AddCommand(command);
    }

    void LoaderGraphProcessor::ChildRemoved(Scene::INode *parent, Scene::INode *child) {
        LoaderCommand command;
        LoaderNodeRemovedCommand& cmd = command.node_removed;
        cmd.parent = parent;
        cmd.old_node = child;
        command.command = LoaderCommands::NodeRemoved;
        AddCommand(command);
    }

    bool LoaderGraphProcessor::IsFinish() {
        return m_delete;
    }

    void LoaderGraphProcessor::AddLoadedObject(Scene::INode *node, Core::Object *o) {
        LoaderCommand command;
        LoaderAddLoadedObjectCommand& cmd = command.add_loaded_object;
		command.command = LoaderCommands::AddLoadedObject;
        cmd.node = node;
        cmd.object = o;
        AddCommand(command);
    }

    void LoaderGraphProcessor::Destroy() {

    }

    void LoaderGraphProcessor::WaitProcessingComplete() {
		bool need_lock = m_graph != nullptr;

		if (need_lock)
		{
			m_graph->Lock();
			Process(m_graph->GetRoot(), &LoaderGraphProcessor::Delete);
			m_graph->Unlock();
		}
        m_thread.Join();
    }

    void LoaderGraphProcessor::StopProcessing() {
        m_delete = true;
    }

    bool LoaderGraphProcessor::OnNodeAdded(Scene::INode *node) {
        auto type = node->Get<Core::String>(L"Type");
        if (type && *type == L"FileProxy") {
            Core::String* path = node->Get<Core::String>(L"Filename");
            if (path) {
                LoaderTask task;
                task.task = LoaderTasks::Load;
				task.load_file.node = node;
				(node->GetSceneGraph()->GetSourcePath()  + *path).ToWchar(task.load_file.filename, MAX_PATH);
                AddTask(task);
            }
        }
        return true;
    }

    void LoaderGraphProcessor::AddCommand(LoaderCommand& cmd) {
        m_commands_mutex.Lock();
        m_commands.push_back(cmd);
        m_commands_mutex.Unlock();
    }

    void LoaderGraphProcessor::AddTask(LoaderTask& task) {
        m_tasks_mutex.Lock();
        m_tasks.push_back(task);
        m_tasks_mutex.Unlock();
    }

    bool LoaderGraphProcessor::OnNodeRemoved(Scene::INode* node) {
        node->MarkToDelete();
        return true;
    }
}

PUNK_ENGINE_END
