#include <config.h>
#include "forms/forms.h"

PUNK_ENGINE_BEGIN
namespace Tools {
	
	void EditorMainWindow::OnViewModules(wxRibbonToolBarEvent& event) {
		ModuleManagerDialog* dlg = new ModuleManagerDialog(this);
		dlg->ShowModal();
		dlg->Destroy();
	}

	void EditorMainWindow::OnLoadModule(wxRibbonToolBarEvent& event) {

	}

	void EditorMainWindow::OnUnloadModule(wxRibbonToolBarEvent& event) {
	
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
//			HWND hwnd = (HWND)m_mid_panel->GetHandle();
//
//
//			m_canvas = System::CreateInstancePtr<Graphics::ICanvas>(
//				Graphics::CLSID_Canvas, Graphics::IID_ICanvas);
//
//			auto desc = Graphics::CanvasDescription();
//			desc.use_parent_window = true;
//			desc.parent_wnd = hwnd;
//
//			m_canvas->Initialize(desc);
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
//		if (m_canvas)
//		m_canvas->GetWindow()->SetSize(m_mid_panel->GetSize().GetWidth(), m_mid_panel->GetSize().GetHeight());
//		event.Skip();
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