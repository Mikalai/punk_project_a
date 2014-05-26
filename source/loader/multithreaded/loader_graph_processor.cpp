#include <core/ifactory.h>
#include <core/iobject.h>
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

	LoaderGraphProcessor::~LoaderGraphProcessor() {}

	void LoaderGraphProcessor::BeginPreProcessSync() {
		//	unlocked at the EndPostProcessSync
		m_process_mutex.Lock();
		if (m_scene_manager->Get) {
			m_scene->Lock();
		}
	}

	void LoaderGraphProcessor::PreProcess() {
		m_sync_thread.Lock();
		auto commands = m_sync_commands;
		m_sync_commands.clear();
		m_sync_thread.Unlock();

		for (auto cmd : commands) {
			ProcessCommand(cmd);
			delete cmd;
		}
	}

	void LoaderGraphProcessor::EndPreProcessSync() {
		if (m_scene) {
			m_scene->Unlock();
		}
	}

	void LoaderGraphProcessor::BeginPostProcessSync() {
		if (m_scene) {
			m_scene->Lock();
		}
	}

	void LoaderGraphProcessor::PostProcess() {
		m_sync_thread.Lock();
		auto commands = m_sync_commands;
		m_sync_commands.clear();
		m_sync_thread.Unlock();

		for (auto cmd : commands) {
			ProcessCommand(cmd);
			delete cmd;
		}
	}

	void LoaderGraphProcessor::EndPostProcessSync() {
		if (m_scene) {
			m_scene->Unlock();
		}
		//	locked at the beginning of the processing loop
		m_process_mutex.Lock();
	}

	void LoaderGraphProcessor::InternalProcess() {
		m_async_thread.Lock();
		auto commands = m_async_commands;
		m_async_commands.clear();
		m_async_thread.Unlock();
	}

	void LoaderGraphProcessor::SendAsyncCommand(Scene::CommandBase* cmd) {
		m_async_thread.Lock();
		m_async_commands.push_back(cmd);
		m_async_thread.Unlock();
	}

	void LoaderGraphProcessor::SendSyncCommand(Scene::CommandBase* cmd) {
		m_sync_thread.Lock();
		m_sync_commands.push_back(cmd);
		m_sync_thread.Unlock();
	}

	void LoaderGraphProcessor::WaitComplete() {
		m_process_mutex.Lock();
		while (!m_async_commands.empty()) {
			delete m_async_commands.back();
			m_async_commands.pop_back();
		}
		while (!m_sync_commands.empty()) {
			delete m_sync_commands.back();
			m_sync_commands.pop_back();
		}
		m_process_mutex.Unlock();
	}

	void LoaderGraphProcessor::Terminate() {
		WaitComplete();
	}

	void LoaderGraphProcessor::ProcessCommand(Scene::CommandBase* cmd) {
		if (cmd->domain == LoaderDomain) {
			ProcessLoaderDomainCommands(cmd);
		}
	}

	void LoaderGraphProcessor::ProcessLoaderDomainCommands(Scene::CommandBase* cmd) {
		switch ((LoaderCommands)cmd->index)
		{
		case LoaderCommands::Add:
			ProcessLoaderAddCommand((CmdAdd*)cmd);
			break;
		case LoaderCommands::Remove:
			ProcessLoaderRemoveCommand((CmdRemove*)cmd);
			break;
		case LoaderCommands::NodeAdded:
			ProcessLoaderNodeAddedCommand((CmdNodeAdded*)cmd);
			break;
		case LoaderCommands::NodeRemoved:
			ProcessLoaderNodeRemovedCommand((CmdNodeRemoved*)cmd);
			break;
		case LoaderCommands::AddLoadedObject:
			ProcessLoaderAddLoadedObjectCommand((CmdAddLoadedObject*)cmd);
			break;
		case LoaderCommands::SetNewGraph:
			ProcessLoaderSetNewGraphCommand((CmdSetGraph*)cmd);
			break;
		case LoaderCommands::LoadFile:
			ProcessLoaderLoadFileCommand((CmdLoadFile*)cmd);
			break;
		default:
			break;
		}
	}

	void LoaderGraphProcessor::ProcessLoaderAddCommand(CmdAdd* cmd) {

	}

	void LoaderGraphProcessor::ProcessLoaderRemoveCommand(CmdRemove* cmd) {}

	void LoaderGraphProcessor::ProcessLoaderNodeAddedCommand(CmdNodeAdded* cmd) {}

	void LoaderGraphProcessor::ProcessLoaderNodeRemovedCommand(CmdNodeRemoved* cmd) {}
	
	void LoaderGraphProcessor::ProcessLoaderAddLoadedObjectCommand(CmdAddLoadedObject* cmd) {}
	
	void LoaderGraphProcessor::ProcessLoaderSetNewGraphCommand(CmdSetGraph* cmd) {
		if (m_scene) {
			FlushCommands();
		}
		m_scene = cmd->new_graph;		
	}

	void LoaderGraphProcessor::ProcessLoaderLoadFileCommand(CmdLoadFile* cmd) {
		Core::IObject* o = ParsePunkFile(cmd->filename);
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

	void LoaderGraphProcessor::OnInternalUpdate(Scene::CommandBase* cmd)
	{
		if (cmd->domain != LoaderDomain)
			throw Error::LoaderException("Can't process internall command. Wrong domain.");
		if (cmd->index == (int)LoaderCommands::LoadFile) {

		}
		else if (cmd->index == (int)LoaderCommands::SetNewGraph) {			
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
			SetGraph(set_graph->new_graph);
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
		Scene::INode* child{ nullptr };
		Core::GetFactory()->CreateInstance(Scene::IID_INode, (void**)&child);
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
		SendAsyncCommand(task);
	}

	bool LoaderGraphProcessor::Process(Scene::INode *node, bool (LoaderGraphProcessor::*func)(Scene::INode *)) {
		if ((this->*func)(node)) {
			for (std::uint64_t i = 0, max_i = node->GetChildrenCount(); i < max_i; ++i) {
				Scene::INode* child = dynamic_cast<Scene::INode*>(node->GetChild(i));
				if (child)
				if (Process(child, func))
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
		SendSyncCommand(cmd);
	}

	void LoaderGraphProcessor::RemoveChild(Scene::INode *parent, Scene::INode *child) {
		CmdRemove* cmd = new CmdRemove;
		cmd->child = child;
		cmd->parent = parent;
		SendSyncCommand(cmd);
	}

	void LoaderGraphProcessor::ChildAdded(Scene::INode *parent, Scene::INode *child) {
		CmdNodeAdded* cmd = new CmdNodeAdded;
		cmd->parent = parent;
		cmd->new_node = child;
		SendSyncCommand(cmd);
	}

	void LoaderGraphProcessor::ChildRemoved(Scene::INode *parent, Scene::INode *child) {
		CmdNodeRemoved* cmd = new CmdNodeRemoved;
		cmd->parent = parent;
		cmd->old_node = child;
		SendSyncCommand(cmd);
	}

	void LoaderGraphProcessor::AddLoadedObject(Scene::INode *node, Core::IObject *o) {
		CmdAddLoadedObject* cmd = new CmdAddLoadedObject;
		cmd->node = node;
		cmd->object = o;
		SendSyncCommand(cmd);
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
				SendAsyncCommand(task);
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
