// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <config.h>
#include "forms/forms.h"

PUNK_ENGINE_BEGIN
namespace Tools {
	class MyApp : public wxApp
	{
	public:
		virtual bool OnInit();
	};


	bool MyApp::OnInit()
	{
		EditorMainWindow *frame = new EditorMainWindow(nullptr);
		frame->Show(true);
		return true;
	}
}
PUNK_ENGINE_END

wxIMPLEMENT_APP(Punk::Engine::Tools::MyApp);