// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <config.h>
#include "editor_main_window.h"

PUNK_ENGINE_BEGIN
namespace Tools {
	class MyApp : public wxApp
	{
	public:
		virtual bool OnInit();
	};


	bool MyApp::OnInit()
	{
		try{
			EditorMainWindow *frame = new EditorMainWindow(nullptr);
			frame->Show(true);
			return true;
		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
		}
	}
}
PUNK_ENGINE_END

wxIMPLEMENT_APP(Punk::Engine::Tools::MyApp);