#include <config.h>
#include <punk_engine.h>
#include "common.h"
#include "forms/create_scene_dialog_impl.h"
#include "editor_main_window.h"

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
		data.push_back(wxString((wchar_t*)time.Data(), (wchar_t*)time.Data()+time.Length()));
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
			auto module = Common::GetSceneModule();
			auto scene_manager = module->GetSceneManager();			
			scene_manager->AddScene(dlg.GetCreatedScene());
			UpdateScenePanel();
		}
		event.Skip();
	}

	void EditorMainWindow::OnSceneDelete(wxRibbonToolBarEvent& event) {
		auto index = m_scenes_combobox->GetSelection();
		if (index != wxNOT_FOUND) {
			std::uint32_t scene_index = (std::uint32_t)m_scenes_combobox->GetClientData(index);
			auto module = Common::GetSceneModule();
			auto scene_manager = module->GetSceneManager();
			scene_manager->RemoveScene(scene_index);
			UpdateScenePanel();
		}
		event.Skip();
	}

	void EditorMainWindow::OnNodeCreate(wxRibbonToolBarEvent& event) {
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
		if (scene_manager->GetScenesCount() != 0)
			m_scenes_combobox->Enable();
		else
			m_scenes_combobox->Disable();
	}

	void EditorMainWindow::OnSceneChanged(wxCommandEvent& event) {
		event.Skip();
	}
}
PUNK_ENGINE_END

//
//	EditorMainWindow::EditorMainWindow(const wxString& title, const wxPoint& pos, const wxSize& size)
//		: wxFrame(NULL, wxID_ANY, title, pos, size)
//	{
//		wxMenu *menuFile = new wxMenu;
//		menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
//			"Help string shown in status bar for this menu item");
//		menuFile->AppendSeparator();
//		menuFile->Append(wxID_EXIT);
//
//		wxMenu *menuHelp = new wxMenu;
//		menuHelp->Append(wxID_ABOUT);
//
//		wxMenu* menuScene = new wxMenu;
//		menuScene->Append(ID_Tree_View, "&Tree view");
//		menuScene->AppendSeparator();
//		menuScene->Append(ID_Load_Any, "&Load punk file");
//
//		wxMenu* menuEngine = new wxMenu;
//		menuEngine->Append(ID_Module_Manager, "&Module manager");		
//
//		wxMenuBar *menuBar = new wxMenuBar;
//		menuBar->Append(menuFile, "&File");
//		menuBar->Append(menuScene, "&Scene");
//		menuBar->Append(menuEngine, "&Engine");
//		menuBar->Append(menuHelp, "&Help");		
//
//		SetMenuBar(menuBar);
//		CreateStatusBar();
//		SetStatusText("Welcome to wxWidgets!");
//
//		wxColour col1, col2;
//		col1.Set(wxT("#4f5049"));
//		col2.Set(wxT("#ededed"));
//
//		wxPanel *panel = new wxPanel(this, -1);
//		panel->SetBackgroundColour(col1);
//		wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
//
//		m_mid_panel = new wxPanel(panel, wxID_ANY);
//		m_mid_panel->SetBackgroundColour(col2);
//
//		vbox->Add(m_mid_panel, 1, wxEXPAND | wxALL, 2);
//		panel->SetSizer(vbox);
//		
//		Centre();
//
//
//		wxTimer* timer = new wxTimer(this, ID_Timer);
//		timer->Start(1000);
//	}
//	void EditorMainWindow::OnExit(wxCommandEvent& event)
//	{
//		Close(true);
//	}
//	void EditorMainWindow::OnAbout(wxCommandEvent& event)
//	{
//		wxMessageBox("This is a wxWidgets' Hello world sample",
//			"About Hello World", wxOK | wxICON_INFORMATION);
//	}
//	void EditorMainWindow::OnHello(wxCommandEvent& event)
//	{		
//		wxLogMessage("Hello world from wxWidgets!");
//	}
//
//	void EditorMainWindow::OnTimer(wxTimerEvent& event) {
//		static bool v = false;
//		/*if (!v) {
//			m_canvas->GetWindow()->Open();
//			v = true;
//		}*/
//		//auto interval = event.GetInterval();
//		////wxMessageBox("Timer shoot");
//		//m_canvas->GetWindow()->Update(interval);
//		//m_canvas->SwapBuffers();
//	}
//
//	void EditorMainWindow::OnResize(wxSizeEvent& event) {
//	}
//
//	void EditorMainWindow::OnSceneTreeView(wxCommandEvent& event) {
//		SceneTreeView* view = new SceneTreeView(this, "Scene", wxPoint(100, 100), wxSize(200, 200));
//		view->ShowModal();
//	}
//
//	void EditorMainWindow::OnModuleManager(wxCommandEvent& event) {
//		ModuleManagerDialog* dialog = new ModuleManagerDialog(this);
//		dialog->ShowModal();
//		dialog->Destroy();
//	}
//
//	wxBEGIN_EVENT_TABLE(EditorMainWindow, wxFrame)
//		EVT_MENU(ID_Hello, EditorMainWindow::OnHello)
//		EVT_MENU(wxID_EXIT, EditorMainWindow::OnExit)
//		EVT_MENU(wxID_ABOUT, EditorMainWindow::OnAbout)
//		EVT_MENU(ID_Tree_View, EditorMainWindow::OnSceneTreeView)
//		EVT_MENU(ID_Module_Manager, EditorMainWindow::OnModuleManager)
//		EVT_SIZE(EditorMainWindow::OnResize)
//		EVT_TIMER(ID_Timer, EditorMainWindow::OnTimer)
//		wxEND_EVENT_TABLE()
//}
//
//PUNK_ENGINE_END