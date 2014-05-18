#include <core/object.h>
#include <attributes/module.h>
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

	const Core::String LoaderGraphProcessor::GetName() const {
		static Core::String name{ "Loader" };
		return name;
	}
	void LoaderGraphProcessor::OnInternalUpdate(Scene::CommandBase* cmd)
	{
		if (cmd->domain != LoaderDomain)
			throw Error::LoaderException("Can't process internall command. Wrong domain.");
		if (cmd->index == (int)LoaderCommands::LoadFile) {
			CmdLoadFile* task = (CmdLoadFile*)cmd;
			Core::IObject* o = ParsePunkFile(task->filename);
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
			OnCmdAddLoadedObject(add_loaded_object);			
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

	void LoaderGraphProcessor::OnCmdAddLoadedObject(CmdAddLoadedObject* add_loaded_object) {
		Scene::INode* node = add_loaded_object->node;
		Core::IObjectUniquePtr object{ add_loaded_object->object, Core::DestroyObject };
		m_logger->Info("Create new node");
		Scene::INode* child = Scene::CreateNode(node);
		child->Set<Core::String>("Owner", GetName());		
		{
			Attributes::IGeometry* geometry = nullptr;
			object->QueryInterface(Attributes::IID_IGeometry, (void**)&geometry);
			if (geometry) {
				child->Set<Attributes::IGeometry>(geometry->GetName(), geometry);
				return;
			}			
		}
		{
			Attributes::ITransform* tranform{ nullptr };
			object->QueryInterface(Attributes::IID_ITransform, (void**)&tranform);
			if (tranform) {
				child->Set<Attributes::ITransform>("Transform", tranform);
				return;
			}
		}
		{
			Attributes::IMaterial* material{ nullptr };
			object->QueryInterface(Attributes::IID_IMaterial, (void**)&material);
			if (material) {
				child->Set<Attributes::IMaterial>(material->GetName(), material);
				return;
			}
		}
		throw Error::LoaderException("Unsupported type");
	}

	void LoaderGraphProcessor::SetGraph(Scene::ISceneGraph *graph) {
		CmdSetGraph* task = new CmdSetGraph;
		task->new_graph = graph;
		AddInternalCommand(task);
	}

	bool LoaderGraphProcessor::Process(Scene::INode *node, bool (LoaderGraphProcessor::*func)(Scene::INode *)) {
		if ((this->*func)(node)) {
			for (std::uint64_t i = 0, max_i = node->GetChildrenCount(); i < max_i; ++i) {
				if (Process(node->GetChild(i), func))
					return true;
			}
		}
		return false;
	}

	bool LoaderGraphProcessor::Delete(Scene::INode *node) {
		node->Remove<Core::IObject>(L"Loader.Data");
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

	void LoaderGraphProcessor::AddLoadedObject(Scene::INode *node, Core::IObject *o) {
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
				m_logger->Info("Loder: " + *path);
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
