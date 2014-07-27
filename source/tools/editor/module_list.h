///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __NONAME_H__
#define __NONAME_H__

#include <config.h>

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/listbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ModuleManagerDialog
///////////////////////////////////////////////////////////////////////////////

PUNK_ENGINE_BEGIN
namespace Tools {
	class ModuleManagerDialog : public wxDialog
	{
	private:

	protected:
		wxListBox* m_loaded_modules_list;
		wxButton* m_add;
		wxButton* m_remove_module;
		wxStaticText* m_module_name;
		wxStaticText* m_name_value;
		wxStaticText* m_module_path;
		wxStaticText* m_module_path_value;
		wxButton* m_ok;

		// Virtual event handlers, overide them in your derived class
		virtual void OnModuleAdd(wxCommandEvent& event) { event.Skip(); }
		virtual void OnModuleRemove(wxCommandEvent& event) { event.Skip(); }
		virtual void OnOk(wxCommandEvent& event) { event.Skip(); }


	public:

		ModuleManagerDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Engine Modules"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1024, 768), long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
		~ModuleManagerDialog();

	};
}
PUNK_ENGINE_END

#endif //__NONAME_H__
