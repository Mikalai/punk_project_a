#include <config.h>
#include <punk_engine.h>
#include <wx/filedlg.h>
#include <wx/menu.h>
#include "common.h"
#include "forms/create_scene_dialog_impl.h"
#include "editor_main_window.h"
#include "action_manager.h"
#include "forms/attribute_dialog_impl.h"

PUNK_ENGINE_BEGIN
namespace Tools {


	void EditorMainWindow::OnViewModules(wxRibbonToolBarEvent& event) {
		ModuleManagerDialog* dlg = new ModuleManagerDialog(this);
		dlg->ShowModal();
		dlg->Destroy();
	}

	EditorMainWindow::EditorMainWindow(wxWindow* parent)
		: EditorMainWindowBase(parent)
	{
		m_log->AppendTextColumn("Time");
		m_log->AppendTextColumn("Severity");
		m_log->AppendTextColumn("Message");

		System::GetDefaultLogger()->AddConsumer(this);

		Common::LoadModules();

		if (!m_canvas) {
			HWND hwnd = (HWND)m_mid_panel->GetHandle();


			m_canvas = System::CreateInstancePtr<Graphics::ICanvas>(
				Graphics::CLSID_Canvas, Graphics::IID_ICanvas);

			auto desc = Graphics::CanvasDescription();
			desc.use_parent_window = true;
			desc.parent_wnd = hwnd;

			m_canvas->Initialize(desc);
			m_canvas->GetWindow()->Open();
		}
	}

	void EditorMainWindow::OnLoadModule(wxRibbonToolBarEvent& event) {

	}

	void EditorMainWindow::OnUnloadModule(wxRibbonToolBarEvent& event) {

	}

	void EditorMainWindow::OnActivate(wxActivateEvent& event) {


		event.Skip();
	}

	void EditorMainWindow::OnIdle(wxIdleEvent& event) {
		auto interval = event.GetTimestamp();
		//wxMessageBox("Timer shoot");
		if (m_canvas) {
			m_canvas->GetWindow()->Update(interval);
			m_canvas->SwapBuffers();
		}
		event.Skip();
	}

	void EditorMainWindow::OnClose(wxCloseEvent& event) {
		Common::Clean();
		event.Skip();
	}

	void EditorMainWindow::OnSize(wxSizeEvent& event) {
		if (m_canvas)
		{
			int w, h;
			m_mid_panel->GetClientSize(&w, &h);
			m_canvas->GetWindow()->SetSize(w, h);
		}
		event.Skip();
	}

	void EditorMainWindow::OnToggleBottomPanel(wxRibbonToolBarEvent& event) {

	}

	void EditorMainWindow::OnToggleLog(wxRibbonToolBarEvent& event) {

	}

	void EditorMainWindow::OnToggleFullscreen(wxRibbonToolBarEvent& event) {
		bool value = !event.GetBar()->GetToolState(event.GetId());
		m_left_panel->Show(value);
		m_bottom_panel->Show(value);
	}

	void EditorMainWindow::Write(const Core::String& time, const Core::String& level, const Core::String &message) {
		wxVector<wxVariant> data;
		data.push_back(wxString((wchar_t*)time.Data(), (wchar_t*)time.Data() + time.Length()));
		data.push_back(wxString((wchar_t*)level.Data(), (wchar_t*)level.Data() + level.Length()));
		data.push_back(wxString((wchar_t*)message.Data(), (wchar_t*)message.Data() + message.Length()));
		m_log->AppendItem(data);
		wxScrollWinEvent e(wxEVT_SCROLLWIN_LINEDOWN, 1, 0);
		e.SetEventObject(m_log);
		m_log->SendAutoScrollEvents(e);
	}

	void EditorMainWindow::OnSceneCreate(wxRibbonToolBarEvent& event) {

		CreateSceneDialogImpl dlg(this);

		class CreateSceneAction : public ActionBase {
		public:
			CreateSceneAction(EditorMainWindow* panel, const Core::String& name)
				: m_name{ name }
				, m_panel{ panel } {}

			void Do() override {
				m_scene = System::CreateInstancePtr<SceneModule::IScene>(SceneModule::CLSID_Scene, SceneModule::IID_IScene);
				m_scene->SetName(m_name);
				auto module = Common::GetSceneModule();
				auto scene_manager = module->GetSceneManager();
				scene_manager->AddScene(m_scene);
				m_panel->UpdateScenePanel();
			}

			virtual void Undo() {
				auto module = Common::GetSceneModule();
				auto scene_manager = module->GetSceneManager();
				auto index = scene_manager->GetSceneIndex(m_scene);
				scene_manager->RemoveScene(index);
				m_panel->UpdateScenePanel();
			}

			virtual void Redo() {
				auto module = Common::GetSceneModule();
				auto scene_manager = module->GetSceneManager();
				scene_manager->AddScene(m_scene);
				m_panel->UpdateScenePanel();
			}

		private:
			EditorMainWindow* m_panel;
			Core::String m_name;
			Core::Pointer<SceneModule::IScene> m_scene{ nullptr, Core::DestroyObject };
		};

		if (dlg.ShowModal() == wxID_OK) {
			ActionManager::Do(new CreateSceneAction(this, Common::WxStringToPunkString(dlg.GetSceneName())));
		}
		event.Skip();
	}

	class DeleteSceneAction : public ActionBase {
	public:
		DeleteSceneAction(EditorMainWindow* panel, Core::Pointer<SceneModule::IScene> scene)
			: m_scene{ scene }
			, m_panel{ panel } {}

		void Do() override {
			auto module = Common::GetSceneModule();
			auto scene_manager = module->GetSceneManager();
			auto index = scene_manager->GetSceneIndex(m_scene);
			scene_manager->RemoveScene(index);
			m_panel->UpdateScenePanel();
		}

		void Undo() override {
			auto module = Common::GetSceneModule();
			auto scene_manager = module->GetSceneManager();
			scene_manager->AddScene(m_scene);
			m_panel->UpdateScenePanel();
		}

		void Redo() override {
			auto module = Common::GetSceneModule();
			auto scene_manager = module->GetSceneManager();
			auto index = scene_manager->GetSceneIndex(m_scene);
			scene_manager->RemoveScene(index);
			m_panel->UpdateScenePanel();
		}

	private:
		EditorMainWindow* m_panel;
		Core::Pointer<SceneModule::IScene> m_scene{ nullptr, Core::DestroyObject };
	};

	void EditorMainWindow::OnSceneDelete(wxRibbonToolBarEvent& event) {

		auto index = m_scenes_combobox->GetSelection();		
		
		if (index != wxNOT_FOUND) {
			std::uint32_t scene_index = (std::uint32_t)m_scenes_combobox->GetClientData(index);
			auto module = Common::GetSceneModule();
			auto scene_manager = module->GetSceneManager();
			auto scene = scene_manager->GetScene(scene_index);
			ActionManager::Do(new DeleteSceneAction(this, scene));
		}
		event.Skip();
	}

	void EditorMainWindow::OnNodeCreate(wxRibbonToolBarEvent& event) {
		if (m_current_scene) {
			auto node = System::CreateInstancePtr<SceneModule::INode>(SceneModule::CLSID_Node, SceneModule::IID_INode);
			if (m_current_node) {				
				m_current_node->AddChild(node);				
			}
			else {
				m_current_scene->SetRoot(node);
			}

			m_scene_tree_graph->GetModel()->ItemAdded(wxDataViewItem{ m_current_node.get() }, wxDataViewItem{ node.get() });
		}
		event.Skip();
	}

	void EditorMainWindow::OnNodeDelete(wxRibbonToolBarEvent& event) {
		event.Skip();
	}

	void EditorMainWindow::UpdateScenePanel() {
		auto module = Common::GetSceneModule();
		auto scene_manager = module->GetSceneManager();
		m_scenes_combobox->Clear();
		for (std::uint32_t i = 0, max_i = scene_manager->GetScenesCount(); i < max_i; ++i) {
			auto scene = scene_manager->GetScene(i);
			m_scenes_combobox->Append(Common::PunkStringToWxString(scene->GetName()), (void*)i);
		}
		if (scene_manager->GetScenesCount() != 0) {
			m_scenes_combobox->Enable();			
		}
		else
			m_scenes_combobox->Disable();
		UpdateSceneGraph();
	}

	struct NodeData : public wxClientData {
		NodeData(Core::Pointer < SceneModule::INode > node)
			: m_node{ node } {}

		Core::Pointer<SceneModule::INode> m_node;
	};

	class SceneDataModule : public wxDataViewModel {
	public:
		SceneDataModule(Core::Pointer<SceneModule::IScene> scene)
			: m_scene{ scene } {}

		unsigned int GetColumnCount() const override {
			return 2;
		}

		// return type as reported by wxVariant
		wxString GetColumnType(unsigned int col) const {
			return "Text";
		}

		// get value into a wxVariant
		void GetValue(wxVariant &variant, const wxDataViewItem &item, unsigned int col) const override {
			Core::Pointer<SceneModule::INode> node{ nullptr, Core::DestroyObject };
			Core::Pointer<SceneModule::IAttribute> attribute{ nullptr, Core::DestroyObject };
			if (!item.IsOk()) {
				node = m_scene->GetRoot();
			}
			else {
				auto o = Core::Pointer < Core::IObject > {(Core::IObject*)item.GetID(), Core::DestroyObject};
				node = Core::QueryInterfacePtr<SceneModule::INode>(o, SceneModule::IID_INode);
				attribute = Core::QueryInterfacePtr<SceneModule::IAttribute>(o, SceneModule::IID_IAttribute);
			}
			if (node) {
				variant = "Node";
			}
			else if (attribute) {
				if (col == 0) {
					variant = Common::PunkStringToWxString(attribute->GetName());
				}
				else {
					variant = "Attribute";
				}
			}
			else {
				variant = "Unknown";
			}
		}

		virtual bool SetValue(const wxVariant &variant, const wxDataViewItem &item, unsigned int col) {
			Core::Pointer<SceneModule::INode> node{ nullptr, Core::DestroyObject };
			if (!item.IsOk()) {
				node = m_scene->GetRoot();
			}
			else {
				auto o = Core::Pointer < Core::IObject > {(Core::IObject*)item.GetID(), Core::DestroyObject};
				node = Core::QueryInterfacePtr<SceneModule::INode>(o, SceneModule::IID_INode);
			}
			return true;
		}

		// define hierarchy
		virtual wxDataViewItem GetParent(const wxDataViewItem &item) const {
			if (!item.IsOk())
				return wxDataViewItem{ nullptr };
			auto o = Core::Pointer < Core::IObject > {(Core::IObject*)item.GetID(), Core::DestroyObject};
			auto node = Core::QueryInterfacePtr<SceneModule::INode>(o, SceneModule::IID_INode);
			if (node) {
				return wxDataViewItem{ (void*)node->GetParent() };
			}
			auto attribute = Core::QueryInterfacePtr<SceneModule::IAttribute>(o, SceneModule::IID_IAttribute);
			if (attribute) {
				return wxDataViewItem{ (void*)attribute->GetOwner() };
			}
			return wxDataViewItem{ nullptr };
		}

		virtual bool IsContainer(const wxDataViewItem &item) const {
			if (!item.IsOk()) {
				if (m_scene.get() && m_scene->GetRoot().get())
					return m_scene->GetRoot()->GetChildrenCount() != 0;
			}
			auto o = Core::Pointer < Core::IObject > {(Core::IObject*)item.GetID(), Core::DestroyObject};
			auto node = Core::QueryInterfacePtr<SceneModule::INode>(o, SceneModule::IID_INode);
			if (node) {
				return node->GetChildrenCount() != 0;
			}
			return false;
		}
		
		virtual unsigned int GetChildren(const wxDataViewItem &item, wxDataViewItemArray &children) const {
			Core::Pointer<SceneModule::INode> node{ nullptr, Core::DestroyObject };
			if (!item.IsOk()) {
				node = m_scene->GetRoot();
				if (node) {
					children.push_back(wxDataViewItem{ node.get() });
					return 1;
				}
				else {
					return 0;
				}
			}
			else {
				auto o = Core::Pointer < Core::IObject > {(Core::IObject*)item.GetID(), Core::DestroyObject};
				node = Core::QueryInterfacePtr<SceneModule::INode>(o, SceneModule::IID_INode);
			}

			if (node) {
				std::uint32_t count = node->GetChildrenCount();
				for (std::uint32_t i = 0, max_i = count; i < max_i; ++i) {
					children.push_back(wxDataViewItem{ (void*)node->GetChild(i).get() });
				}
				count += node->GetAttributesCount();
				for (std::uint32_t i = 0, max_i = node->GetAttributesCount(); i < max_i; ++i) {
					children.push_back(wxDataViewItem{ (void*)node->GetAttribute(i).get() });
				}
				return count;
			}
			return 0;
		}

	private:
		Core::Pointer<SceneModule::IScene> m_scene;
	};

	void EditorMainWindow::UpdateSceneGraph() {
		m_scene_tree_graph->ClearColumns();
		
		m_scene_tree_graph->AppendTextColumn("Name", 0);		
		m_scene_tree_graph->AppendTextColumn("Type", 1);
		
		auto index = m_scenes_combobox->GetSelection();

		if (index != wxNOT_FOUND) {
			std::uint32_t scene_index = (std::uint32_t)m_scenes_combobox->GetClientData(index);
			auto module = Common::GetSceneModule();
			auto scene_manager = module->GetSceneManager();
			m_current_scene = scene_manager->GetScene(scene_index);

			auto model = new SceneDataModule{ m_current_scene };
			m_scene_tree_graph->AssociateModel(model);
			model->DecRef();

			//if (scene->GetRoot()) {
			//	std::stack<Core::Pointer<SceneModule::INode>> nodes;
			//	std::stack<wxDataViewItem> parents;
			//	nodes.push(scene->GetRoot());
			//	parents.push(wxDataViewItem{ nullptr });

			//	/*while (!nodes.empty()) {
			//		auto node = nodes.top();
			//		nodes.pop();
			//		auto parent = parents.top();
			//		parents.pop();
			//		parent = m_scene_tree_graph->AppendContainer(parent, "Node", 0, -1, new NodeData{ node });
			//		m_scene_tree_graph->SetItemText(parent, "Node");					
			//		for (std::uint32_t i = 0, max_i = node->GetChildrenCount(); i < max_i; ++i) {
			//			nodes.push(node->GetChild(i));
			//			parents.push(parent);
			//		}
			//	}*/
			//}
		}
	}

	void EditorMainWindow::OnSceneChanged(wxCommandEvent& event) {
		UpdateSceneGraph();
		auto index = event.GetSelection();
		event.Skip();
	}

	void EditorMainWindow::OnUndo(wxRibbonToolBarEvent& event) {
		ActionManager::Undo();
	}

	void EditorMainWindow::OnRedo(wxRibbonToolBarEvent& event) {
		ActionManager::Redo();
	}

	void EditorMainWindow::OnSwitchDetailedGraph(wxCommandEvent& event) {

	}

	void EditorMainWindow::OnSwitchObjectsGraph(wxCommandEvent& event) {

	}

	void EditorMainWindow::OnSceneGraphItemActivated(wxDataViewEvent& event) {

	}

	void EditorMainWindow::OnSceneGraphItemChanged(wxDataViewEvent& event) {
		auto item = event.GetItem();
		if (!item.IsOk()) {
			if (m_current_scene) {
				m_current_node = m_current_scene->GetRoot();
				return;
			}
		}
		else {
			auto o = Core::Pointer < Core::IObject > {(Core::IObject*)item.GetID(), Core::DestroyObject};
			auto node = Core::QueryInterfacePtr<SceneModule::INode>(o, SceneModule::IID_INode);
			if (node) {
				m_current_node = node;
				return;
			}
			auto attribute = Core::QueryInterfacePtr<SceneModule::IAttribute>(o, SceneModule::IID_IAttribute);
			if (attribute) {
				m_current_attribute = attribute;
			}
		}
	}

	void EditorMainWindow::OnSceneLoad(wxRibbonToolBarEvent& event) {		
		wxFileDialog openFileDialog(this, _("Open scene file"), "", "",
			"Scene files (*.bpmd)|*.bpmd", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

		if (openFileDialog.ShowModal() == wxID_OK){
			wxString filename = openFileDialog.GetFilename();
			auto module = Common::GetIoModule();
			auto object = module->Deserialize(Common::WxStringToPunkString(filename));
			auto scene = Core::QueryInterfacePtr<SceneModule::IScene>(object, SceneModule::IID_IScene);
			if (scene) {
				auto manager = Common::GetSceneModule()->GetSceneManager();
				manager->AddScene(scene);
				UpdateScenePanel();
			}
		}
	}

	void EditorMainWindow::OnSceneSave(wxRibbonToolBarEvent& event) {
		if (m_current_scene) {
			wxFileDialog saveFileDialog(this, _("Save scene file"), "", "",
				"Scene files (*.bpmd)|*.bpmd", wxFD_SAVE);			

			if (saveFileDialog.ShowModal() == wxID_OK){
				wxString filename = saveFileDialog.GetFilename();
				auto module = Common::GetIoModule();
				module->Serialize(m_current_scene, Common::WxStringToPunkString(filename));
			}
		}
	}

	void EditorMainWindow::OnSceneContextMenu(wxDataViewEvent& event) {
		auto item = event.GetItem();
		if (item.IsOk()) {
			auto o = Core::Pointer < Core::IObject > {(Core::IObject*)item.GetID(), Core::DestroyObject};
			auto node = Core::QueryInterfacePtr<SceneModule::INode>(o, SceneModule::IID_INode);
			if (node) {
				wxMenu menu;
				menu.SetClientData((void*)node.get());
				menu.Append(ID_SCENE_MENU_ADD_ATTRIBUTE, "Add attribute");
				menu.Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&EditorMainWindow::OnScenePopUpClick, nullptr, this);
				PopupMenu(&menu);
			}
		}
	}

	void EditorMainWindow::OnScenePopUpClick(wxCommandEvent& event) {
		auto node = (SceneModule::INode*)(static_cast<wxMenu *>(event.GetEventObject())->GetClientData());
		AttributeDialogImpl dlg(this);
		if (dlg.ShowModal() == wxID_OK) {
			auto attribute = dlg.GetAttribute();
			if (attribute) {
				node->AddAttribute(attribute);
				m_scene_tree_graph->GetModel()->ItemAdded(wxDataViewItem{ node }, wxDataViewItem{ attribute.get() });
			}
		}		
	}

}
PUNK_ENGINE_END
