#include <attributes/module.h>
#include <core/object.h>
#include <scene/module.h>
#include <system/module.h>
#include "render_processor.h"
#include "render_commands.h"

PUNK_ENGINE_BEGIN
namespace Render {

	RenderProcessor::RenderProcessor() {}

	RenderProcessor::~RenderProcessor() {}

	const Core::String RenderProcessor::GetName() const {
		static Core::String name{ "Render" };
		return name;
	}

	void RenderProcessor::OnInternalUpdate(int dt) {
		if (m_canvas) {			
			auto driver = m_canvas->GetVideoDriver();
			auto render = driver->GetRender();
			auto frame = render->BeginFrame();
			auto back_buffer = Graphics::GetBackbuffer();
			back_buffer->SetViewport(0, 0, m_canvas->GetWindow()->GetWidth(), m_canvas->GetWindow()->GetHeight());
			back_buffer->SetClearColor(1, 0, 0, 1);
			back_buffer->Bind();
			back_buffer->Clear();					
			frame->DrawLine(0, 0, 100, 100);	
			back_buffer->Unbind();
			render->EndFrame();
			m_canvas->GetWindow()->Update(dt);
			m_canvas->SwapBuffers();
		}
	}

	void RenderProcessor::OnInternalUpdate(Scene::CommandBase* cmd) {
		if (cmd->domain != RenderDomain)
			throw Error::RenderException("Can't process internall command. Wrong domain.");
		if (cmd->index == (int)RenderCommands::SetNewScene)
			OnSetNewGraph((CmdSetNewScene*)cmd);
		else if (cmd->index == (int)RenderCommands::Show) {
			CmdShow* show = (CmdShow*)cmd;
			if (show->visible)
				OnShow();
			else 
				OnHide();
		}
		else if (cmd->index == (int)RenderCommands::CookMesh) {
			CmdCookMesh* cook_mesh = (CmdCookMesh*)cmd;
			OnCookMesh(cook_mesh);
		}
	}

	void RenderProcessor::OnCookMesh(CmdCookMesh* cmd) {
		auto attributes = cmd->node_with_data->GetAttributes(Attributes::StaticGeometry::Type()->GetId());
		for (auto& attribute : attributes) {
			Attributes::StaticGeometry* geom = attribute->Get<Attributes::StaticGeometry>();
			auto p = Graphics::CreateTriangles(0, m_canvas->GetVideoDriver());
			p->
		}
	}

	void RenderProcessor::OnSetNewGraph(CmdSetNewScene* task) {
		AssignGraph(task->graph);
		CmdSetNewScene* command = new CmdSetNewScene;
		command->graph = GetGraph();
		AddCommand(command);

		m_camera_node = GetGraph()->FindNodeByAttribute<Attributes::Camera>("Camera");
		if (m_camera_node == nullptr) {
			auto node = CreateRenderNode("Camera");
			Attributes::Camera* camera = new Attributes::Camera;
			node->Set<Attributes::Camera>("Camera", camera);
			node->Set<Core::String>("Type", Attributes::Camera::Type()->GetName());
			GetGraph()->GetRoot()->AddChild(m_camera_node = node.release());
		}
	}

	Scene::INodeUniquePtr RenderProcessor::CreateRenderNode(const Core::String& name) {
		auto node = Scene::CreateNode();
		node->Set<Core::String>("Owner", GetName());
		node->Set<Core::String>("Name", name);
		return node;
	}

	void RenderProcessor::OnShow() {
		if (m_canvas.get() == nullptr) {
			m_canvas = Graphics::CreateCanvas(Graphics::CanvasDescription());			
			m_canvas->GetWindow()->Open();
		}		
	}

	void RenderProcessor::OnHide() {

	}

	void RenderProcessor::OnPreUpdate(Scene::CommandBase* command) {
	}

	void RenderProcessor::OnPostUpdate(Scene::CommandBase* cmd) {
		if (cmd->index == (int)RenderCommands::SetNewScene) {
			CmdSetNewScene* set_graph = (CmdSetNewScene*)cmd;
			AssignGraph(set_graph->graph);
			GetGraph()->SubscribeOnNodeAdded(new Core::Action<RenderProcessor, Scene::INode*, Scene::INode*>(
				this, &RenderProcessor::ChildAdded));
			GetGraph()->SubscribeOnNodeRemoved(new Core::Action<RenderProcessor, Scene::INode*, Scene::INode*>(
				this, &RenderProcessor::ChildRemoved));
			Process(GetGraph()->GetRoot(), &RenderProcessor::OnNodeAdded);
		}
	}

	void RenderProcessor::SetGraph(Scene::ISceneGraph *graph) {
		CmdSetNewScene* task = new CmdSetNewScene;
		task->graph = graph;
		AddInternalCommand(task);
	}

	bool RenderProcessor::Process(Scene::INode *node, bool (RenderProcessor::*func)(Scene::INode *)) {
		if ((this->*func)(node)) {
			for (std::uint64_t i = 0; i < node->GetChildrenCount(); ++i) {
				if (Process(node->GetChild(i), func))
					return true;
			}
		}
		return false;
	}

	bool RenderProcessor::Delete(Scene::INode *node) {
		return false;
	}

	void RenderProcessor::AddChild(Scene::INode *parent, Scene::INode *child) {
		
	}

	void RenderProcessor::RemoveChild(Scene::INode *parent, Scene::INode *child) {
		
	}

	void RenderProcessor::ChildAdded(Scene::INode *parent, Scene::INode *child) {
		
	}

	void RenderProcessor::ChildRemoved(Scene::INode *parent, Scene::INode *child) {
		
	}

	void RenderProcessor::OnWaitProcessingComplete() {
		Process(GetGraph()->GetRoot(), &RenderProcessor::Delete);
	}

	bool RenderProcessor::OnNodeAdded(Scene::INode *node) {
		auto type = node->Get<Core::String>(L"Type");
		auto name = node->Get<Core::String>("Name");
		auto owner = node->Get<Core::String>("Owner");
		Core::StringList info;
		if (type) {
			info.Push("Type: ");
			info.Push(*type + "; ");
		}
		if (name) {
			info.Push("Name: ");
			info.Push(*name + "; ");
		}
		if (owner) {
			info.Push("Owner: ");
			info.Push(*owner + "; ");
		}
		System::GetDefaultLogger()->Info(info.ToString(""));
		return true;
	}

	bool RenderProcessor::OnNodeRemoved(Scene::INode* node) {
		node->MarkToDelete();
		return true;
	}

	void RenderProcessor::OnStartProcessing() {

	}

	void RenderProcessor::Show(){
		CmdShow* show = new CmdShow;
		AddInternalCommand(show);
	}

	void RenderProcessor::Hide() {
		CmdShow* show = new CmdShow;
		show->visible = false;
		AddInternalCommand(show);
	}
}

PUNK_ENGINE_END
