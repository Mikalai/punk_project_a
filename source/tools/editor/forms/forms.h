///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __FORMS_H__
#define __FORMS_H__

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
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/ribbon/toolbar.h>
#include <wx/ribbon/panel.h>
#include <wx/ribbon/page.h>
#include <wx/ribbon/control.h>
#include <wx/ribbon/art.h>
#include <wx/ribbon/bar.h>
#include <wx/notebook.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

namespace Punk
{
	namespace Engine
	{
		namespace Tools
		{
			#define ID_ENGINE_MODULES_VIEW 1000
			#define ID_ENGINE_MODULES_LOAD 1001
			#define ID_ENGINE_MODULES_UNLOAD 1002
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class ModuleManagerDialog
			///////////////////////////////////////////////////////////////////////////////
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
					void OnClose( wxCloseEvent& event );
					void OnInit( wxInitDialogEvent& event );
					void OnItemSelected( wxCommandEvent& event );
					void OnModuleAdd( wxCommandEvent& event );
					void OnModuleRemove( wxCommandEvent& event );
					void OnOk( wxCommandEvent& event );
					
				
				public:
					
					ModuleManagerDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Engine Modules"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1024,768 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
					~ModuleManagerDialog();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class SceneGraphPanel
			///////////////////////////////////////////////////////////////////////////////
			class SceneGraphPanel : public wxPanel 
			{
				private:
				
				protected:
				
				public:
					
					SceneGraphPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL ); 
					~SceneGraphPanel();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class EditorMainWindow
			///////////////////////////////////////////////////////////////////////////////
			class EditorMainWindow : public wxFrame 
			{
				private:
				
				protected:
					wxNotebook* m_menu;
					wxPanel* m_file_panel;
					wxRibbonBar* m_file_ribbon_bar;
					wxRibbonPage* m_file_page;
					wxRibbonPanel* m_file_ribbon_panel;
					wxRibbonToolBar* m_file_toolbar;
					wxPanel* m_engine_panel;
					wxRibbonBar* m_modules_bar;
					wxRibbonPage* m_modules_page;
					wxRibbonPanel* m_modules_panel;
					wxRibbonToolBar* m_module_toolbar;
					
					// Virtual event handlers, overide them in your derived class
					void OnViewModules( wxRibbonToolBarEvent& event );
					void OnLoadModule( wxRibbonToolBarEvent& event );
					void OnUnloadModule( wxRibbonToolBarEvent& event );
					
				
				public:
					
					EditorMainWindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Punk Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1024,840 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
					
					~EditorMainWindow();
				
			};
			
		} // namespace Tools
	} // namespace Engine
} // namespace Punk

#endif //__FORMS_H__
