#include <config.h>
#include <punk_engine.h>
#include <wx/filedlg.h>
#include <wx/menu.h>
#include "common.h"
#include "forms/create_scene_dialog_impl.h"
#include "editor_main_window.h"
#include "action_manager.h"
#include "forms/attribute_dialog_impl.h"
#include "scene_model.h"
#include "actions.h"

PUNK_ENGINE_BEGIN
namespace Tools {

	void EditorMainWindow::SetCurrentSceneModel(SceneDataModel* model) {
		if (m_scene_model != model) {
			auto old = m_scene_model;
			m_scene_model = model;
			m_scene_tree_graph->AssociateModel(model);
			if (old)
				old->RemoveAllNotifiers();
			m_scene_tree_graph->Update();
		}
	}

	wxComboBox* EditorMainWindow::GetSceneCombobox() {
		return m_scenes_combobox;
	}

	void EditorMainWindow::OnViewModules(wxRibbonToolBarEvent& event) {
		ModuleManagerDialog* dlg = new ModuleManagerDialog(this);
		dlg->ShowModal();
		dlg->Destroy();
	}

	EditorMainWindow::~EditorMainWindow() {
		System::GetDefaultLogger()->RemoveConsumer(this);
	}

	EditorMainWindow::EditorMainWindow(wxWindow* parent)
		try
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

		m_scene_tree_graph->ClearColumns();
		m_scene_tree_graph->EnableDragSource(wxDF_UNICODETEXT);
		m_scene_tree_graph->EnableDropTarget(wxDF_UNICODETEXT);

		m_scene_tree_graph->AppendTextColumn("Name", 0);
		m_scene_tree_graph->AppendTextColumn("Type", 1);
	}
	catch (...) {
		System::GetDefaultLogger()->RemoveConsumer(this);
		throw;
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


		if (dlg.ShowModal() == wxID_OK) {
			ActionManager::Do(new CreateSceneAction(this, Common::WxStringToPunkString(dlg.GetSceneName())));
		}
		event.Skip();
	}


	void EditorMainWindow::OnSceneDelete(wxRibbonToolBarEvent& event) {

		auto index = m_scenes_combobox->GetSelection();

		if (index != wxNOT_FOUND) {
			std::uint32_t scene_index = (std::uint32_t)m_scenes_combobox->GetClientData(index);
			auto module = Common::GetSceneModule();
			auto scene_manager = module->GetSceneManager();
			auto scene = scene_manager->GetScene(scene_index);
			ActionManager::Do(new DeleteSceneAction(this));
		}
		event.Skip();
	}

	void EditorMainWindow::OnNodeCreate(wxRibbonToolBarEvent& event) {
		if (m_scene_model) {
			ActionManager::Do(new CreateNodeAction(this, m_current_node));
		}
		event.Skip();
	}

	void EditorMainWindow::OnNodeDelete(wxRibbonToolBarEvent& event) {
		event.Skip();
	}

	struct NodeData : public wxClientData {
		NodeData(Core::Pointer < SceneModule::INode > node)
			: m_node{ node } {}

		Core::Pointer<SceneModule::INode> m_node;
	};

	SceneDataModel* EditorMainWindow::GetCurrentSceneModel() {
		return m_scene_model;
	}

	void EditorMainWindow::UpdateSceneGraph() {

		auto index = m_scenes_combobox->GetSelection();
		if (index != wxNOT_FOUND) {
			auto scene_model = (SceneDataModel*)m_scenes_combobox->GetClientData(index);
			SetCurrentSceneModel(scene_model);
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
		auto item = event.GetItem();
		auto o = Core::Pointer < Core::IObject > {(Core::IObject*)item.GetID(), Core::DestroyObject};
		auto attribute = Core::QueryInterfacePtr<SceneModule::IAttribute>(o, SceneModule::IID_IAttribute);
		if (attribute) {
			AttributeDialogImpl dlg(this);
			dlg.SetObject(attribute->GetRawData());
			dlg.SetObjectName(attribute->GetName());
			dlg.ShowModal();
			attribute->SetName(dlg.GetObjectName());
			attribute->SetRawData(dlg.GetObject());
		}
	}

	void EditorMainWindow::OnSceneGraphItemChanged(wxDataViewEvent& event) {
		auto item = event.GetItem();
		if (!item.IsOk()) {
			if (m_scene_model && m_scene_model->GetScene()) {
				m_current_node = m_scene_model->GetScene()->GetRoot();
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

		if (openFileDialog.ShowModal() == wxID_OK) {
			wxString filename = openFileDialog.GetFilename();
			auto module = Common::GetIoModule();
			auto object = module->Deserialize(Common::WxStringToPunkString(filename));
			auto scene = Core::QueryInterfacePtr<SceneModule::IScene>(object, SceneModule::IID_IScene);
			if (scene) {
				auto manager = Common::GetSceneModule()->GetSceneManager();
				manager->AddScene(scene);
				//UpdateScenePanel();
			}
		}
	}

	void EditorMainWindow::OnSceneSave(wxRibbonToolBarEvent& event) {
		if (m_scene_model && m_scene_model->GetScene()) {
			wxFileDialog saveFileDialog(this, _("Save scene file"), "", "",
				"Scene files (*.bpmd)|*.bpmd", wxFD_SAVE);

			if (saveFileDialog.ShowModal() == wxID_OK){
				wxString filename = saveFileDialog.GetFilename();
				auto module = Common::GetIoModule();
				module->Serialize(m_scene_model->GetScene(), Common::WxStringToPunkString(filename));
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
		if (!node)
			return;
		ActionManager::Do(new CreateAttributeAction{ this, Core::Pointer < SceneModule::INode > {node, Core::DestroyObject} });
	}

	void EditorMainWindow::OnSceneDragBegin(wxDataViewEvent& event) {
		if (event.GetItem() != wxDataViewItem(m_scene_model->GetScene()->GetRoot().get())) {

			//m_dragged_item = Core::Pointer < Core::IObject > {(Core::IObject*)event.GetItem().GetID(), Core::DestroyObject};
			m_dragged_item = event.GetItem();
			//event.SetDragFlags(wxDrag_DefaultMove);

			wxTextDataObject *obj = new wxTextDataObject;
			obj->SetText("Item");
			event.SetDataObject(obj);
			event.SetDragFlags(wxDrag_AllowMove); // allows both copy and move
			//event.Allow();
		}
		else {
			event.Veto();
			//event.Skip();
		}
	}

	void EditorMainWindow::OnSceneCheckDrop(wxDataViewEvent& event) {
		auto o = Core::Pointer < Core::IObject > {(Core::IObject*)event.GetItem().GetID(), Core::DestroyObject};
		auto destination_node = Core::QueryInterfacePtr < SceneModule::INode >(o, SceneModule::IID_INode);
		auto dst_attribute = Core::QueryInterfacePtr < SceneModule::IAttribute >(o, SceneModule::IID_IAttribute);
		if (destination_node){
			//event.Allow();
		}
		else
			event.Veto();
	}

	void EditorMainWindow::OnSceneDragDrop(wxDataViewEvent& event) {
		Core::Pointer<SceneModule::INode> source_node{ nullptr, Core::DestroyObject };
		Core::Pointer<SceneModule::INode> destination_node{ nullptr, Core::DestroyObject };
		Core::Pointer<SceneModule::INode> dragged_node{ nullptr, Core::DestroyObject };
		Core::Pointer<SceneModule::IAttribute> dragged_attribute{ nullptr, Core::DestroyObject };

		{
			auto o = Core::Pointer < Core::IObject > {(Core::IObject*)m_dragged_item.GetID(), Core::DestroyObject};
			dragged_node = Core::QueryInterfacePtr<SceneModule::INode>(o, SceneModule::IID_INode);
			dragged_attribute = Core::QueryInterfacePtr<SceneModule::IAttribute>(o, SceneModule::IID_IAttribute);
		}

		if (dragged_node)
			source_node.reset(dragged_node->GetParent());
		if (dragged_attribute)
			source_node.reset(dragged_attribute->GetOwner());

		{
			auto o = Core::Pointer < Core::IObject > {(Core::IObject*)event.GetItem().GetID(), Core::DestroyObject};
			destination_node = Core::QueryInterfacePtr < SceneModule::INode >(o, SceneModule::IID_INode);
			auto dst_attribute = Core::QueryInterfacePtr < SceneModule::IAttribute >(o, SceneModule::IID_IAttribute);
			if (!destination_node){
				destination_node.reset(dst_attribute->GetOwner());
			}
		}

		if (event.GetItem().IsOk()) {
			if (source_node && destination_node && source_node != destination_node) {
				if (dragged_node && dragged_node != source_node && dragged_node != destination_node) {
					ActionManager::Do(new DragItemAction{ this, source_node, destination_node, dragged_node });
				}
				else if (dragged_attribute) {
					ActionManager::Do(new DragItemAction{ this, source_node, destination_node, dragged_attribute });
				}
				else {
					event.Veto();
				}
			}
			else
				event.Veto();
		}
		else
			event.Veto();
	}
}
PUNK_ENGINE_END
