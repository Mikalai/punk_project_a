#include <core/object.h>
#include <loader/parser/parse_punk_file.h>
#include "loader/error/loader_error.h"
#include "loader_cache.h"
#include "loader_graph_processor.h"
#include "async_parser.h"

PUNK_ENGINE_BEGIN
namespace Loader {

	LoaderGraphProcessor::LoaderGraphProcessor()
	{
	}

	void LoaderGraphProcessor::OnInternalUpdate(Scene::CommandBase* cmd)
	{
		if (cmd->domain != LoaderDomain)
			throw Error::LoaderException("Can't process internall command. Wrong domain.");
		if (cmd->index == (int)LoaderCommands::LoadFile) {
			CmdLoadFile* task = (CmdLoadFile*)cmd;
			Core::Object* o = ParsePunkFile(task->filename);
			auto graph = dynamic_cast<Scene::ISceneGraph*>(o);
			if (graph) {
				auto node = graph->ReleaseRoot();
				AddChild(task->node, node);
				delete graph;
			}
			else {
				auto node = dynamic_cast<Scene::INode*>(o);
				if (node)
					AddChild(task->node, node);
				else {
					AddLoadedObject(task->node, o);
				}
			}
		}
		else if (cmd->index == (int)LoaderCommands::SetNewGraph) {
			CmdSetGraph* task = (CmdSetGraph*)cmd;
			AssignGraph(task->new_graph);
			CmdSetGraph* command = new CmdSetGraph;
			command->new_graph = GetGraph();
			AddCommand(command);
		}

	}

	void LoaderGraphProcessor::OnPreUpdate(Scene::CommandBase* command) {
	}

	void LoaderGraphProcessor::OnPostUpdate(Scene::CommandBase* cmd) {
		if (cmd->index == (int)LoaderCommands::Add) {
			CmdAdd* add = (CmdAdd*)cmd;
			Scene::INode* parent = add->parent;
			Scene::INode* child = add->child;
			parent->AddChild(child);
		}
		else if (cmd->index == (int)LoaderCommands::Remove) {
			CmdRemove* remove = (CmdRemove*)cmd;
			Scene::INode* parent = remove->parent;
			Scene::INode* child = remove->child;
			parent->RemoveChild(child, true);
		}
		else if (cmd->index == (int)LoaderCommands::NodeAdded) {
			CmdNodeAdded* node_added = (CmdNodeAdded*)cmd;
			Process(node_added->new_node, &LoaderGraphProcessor::OnNodeAdded);
		}
		else if (cmd->index == (int)LoaderCommands::NodeRemoved) {
			CmdNodeRemoved* node_removed = (CmdNodeRemoved*)cmd;
			Process(node_removed->old_node, &LoaderGraphProcessor::OnNodeRemoved);
		}
		else if (cmd->index == (int)LoaderCommands::AddLoadedObject) {
			CmdAddLoadedObject* add_loaded_object = (CmdAddLoadedObject*)cmd;
			Scene::INode* node = add_loaded_object->node;
			Core::Object* object = add_loaded_object->object;
			node->Set<Core::Object>(L"Loader.Data", object);
		}
		else if (cmd->index == (int)LoaderCommands::SetNewGraph) {
			CmdSetGraph* set_graph = (CmdSetGraph*)cmd;			
			AssignGraph(set_graph->new_graph);
			GetGraph()->SubscribeOnNodeAdded(new Core::Action<LoaderGraphProcessor, Scene::INode*, Scene::INode*>(
				this, &LoaderGraphProcessor::ChildAdded));
			GetGraph()->SubscribeOnNodeRemoved(new Core::Action<LoaderGraphProcessor, Scene::INode*, Scene::INode*>(
				this, &LoaderGraphProcessor::ChildRemoved));
			Process(GetGraph()->GetRoot(), &LoaderGraphProcessor::OnNodeAdded);			
		}
	}

	void LoaderGraphProcessor::SetGraph(Scene::ISceneGraph *graph) {
		CmdSetGraph* task = new CmdSetGraph;
		task->new_graph = graph;
		AddInternalCommand(task);
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
		CmdAdd* cmd = new CmdAdd;
		cmd->child = child;
		cmd->parent = parent;
		AddCommand(cmd);
	}

	void LoaderGraphProcessor::RemoveChild(Scene::INode *parent, Scene::INode *child) {
		CmdRemove* cmd = new CmdRemove;
		cmd->child = child;
		cmd->parent = parent;
		AddCommand(cmd);
	}

	void LoaderGraphProcessor::ChildAdded(Scene::INode *parent, Scene::INode *child) {
		CmdNodeAdded* cmd = new CmdNodeAdded;
		cmd->parent = parent;
		cmd->new_node = child;
		AddCommand(cmd);
	}

	void LoaderGraphProcessor::ChildRemoved(Scene::INode *parent, Scene::INode *child) {
		CmdNodeRemoved* cmd = new CmdNodeRemoved;
		cmd->parent = parent;
		cmd->old_node = child;
		AddCommand(cmd);
	}

	void LoaderGraphProcessor::AddLoadedObject(Scene::INode *node, Core::Object *o) {
		CmdAddLoadedObject* cmd = new CmdAddLoadedObject;
		cmd->node = node;
		cmd->object = o;
		AddCommand(cmd);
	}


	void LoaderGraphProcessor::OnWaitProcessingComplete() {
		Process(GetGraph()->GetRoot(), &LoaderGraphProcessor::Delete);
	}

	bool LoaderGraphProcessor::OnNodeAdded(Scene::INode *node) {
		auto type = node->Get<Core::String>(L"Type");
		if (type && *type == L"FileProxy") {
			Core::String* path = node->Get<Core::String>(L"Filename");
			if (path) {
				CmdLoadFile* task = new CmdLoadFile;
				task->node = node;
				task->filename = node->GetSceneGraph()->GetSourcePath() + *path;
				AddInternalCommand(task);
			}
		}
		return true;
	}

	bool LoaderGraphProcessor::OnNodeRemoved(Scene::INode* node) {
		node->MarkToDelete();
		return true;
	}

	void LoaderGraphProcessor::OnStartProcessing() {

	}
}

PUNK_ENGINE_END
