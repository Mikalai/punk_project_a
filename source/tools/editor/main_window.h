#ifndef _H_MAIN_WINDOW
#define _H_MAIN_WINDOW

#include <punk_engine.h>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Tools {	

	enum
	{
		ID_Hello = 1,
		ID_Tree_View = 2,
		ID_Load_Any = 3,
		ID_Timer = 4,
		ID_Module_Manager = 5
	};

	class EditorMainWindow : public wxFrame
	{
	public:
		EditorMainWindow(const wxString& title, const wxPoint& pos, const wxSize& size);
	private:
		void OnHello(wxCommandEvent& event);
		void OnExit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		void OnSceneTreeView(wxCommandEvent& event);
		void OnModuleManager(wxCommandEvent& event);
		void OnTimer(wxTimerEvent& event);
		void OnResize(wxSizeEvent& event);
		wxDECLARE_EVENT_TABLE();

	private:
		Core::Pointer<Graphics::ICanvas> m_canvas{ nullptr, Core::DestroyObject };
		wxPanel* m_mid_panel{ nullptr };
	};
}

PUNK_ENGINE_END

#endif	//	_H_MAIN_WINDOW