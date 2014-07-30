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
#include <wx/combobox.h>
#include <wx/dataview.h>
#include <wx/notebook.h>
#include <wx/frame.h>
#include <wx/textctrl.h>

///////////////////////////////////////////////////////////////////////////

namespace Punk
{
	namespace Engine
	{
		namespace Tools
		{
			#define ID_EDITOR_PANEL_MANAGER_TOGGLE_BOTTOM_PANEL 1000
			#define ID_EDITOR_TOGGLE_BOTTOM_PANEL 1001
			#define ID_EDITOR_TOGGLE_LOG 1002
			#define ID_EDITOR_TOGGLE_FULLSCREEN 1003
			#define ID_ENGINE_MODULES_VIEW 1004
			#define ID_ENGINE_MODULES_LOAD 1005
			#define ID_ENGINE_MODULES_UNLOAD 1006
			#define ID_SCENE_ASSETS_LOAD 1007
			#define ID_SCENE_ASSETS_REMOVE 1008
			#define ID_SCENE_ASSETS_PROPERTY 1009
			#define ID_SCENE_NEW_SCENE 1010
			#define ID_SCENE_DELETE_SCENE 1011
			#define ID_SCENE_NEW_NODE 1012
			#define ID_SCENE_NODE_DELETE 1013
			#define ID_SCENE_PANEL 1014
			#define ID_CREATE_SCENE_OK 1015
			
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
			/// Class EditorMainWindowBase
			///////////////////////////////////////////////////////////////////////////////
			class EditorMainWindowBase : public wxFrame 
			{
				private:
				
				protected:
					wxRibbonBar* m_scene_ribbon_bar;
					wxRibbonPage* m_editor_page;
					wxRibbonPanel* m_file_ribbon_panel;
					wxRibbonToolBar* m_file_toolbar;
					wxRibbonPanel* m_tools_manager;
					wxRibbonToolBar* m_panel_manager_toolbar;
					wxRibbonPage* m_engine_page;
					wxRibbonPanel* m_modules_panel;
					wxRibbonToolBar* m_module_toolbar;
					wxRibbonPage* m_scene_assets_page;
					wxRibbonPanel* m_assets_manager_panel;
					wxRibbonToolBar* m_assets_manager_toolbar;
					wxRibbonPanel* m_node_panel;
					wxRibbonToolBar* m_node_panel_bar;
					wxPanel* m_left_panel;
					wxNotebook* m_left_notebook;
					wxPanel* m_scene_panel;
					wxComboBox* m_scenes_combobox;
					wxDataViewTreeCtrl* m_dataViewTreeCtrl1;
					wxPanel* m_mid_panel;
					wxPanel* m_bottom_panel;
					wxNotebook* m_bottom_panel_stuff;
					wxPanel* m_log_panel;
					wxDataViewListCtrl* m_log;
					
					// Virtual event handlers, overide them in your derived class
					virtual void OnActivate( wxActivateEvent& event ) = 0;
					virtual void OnClose( wxCloseEvent& event ) = 0;
					virtual void OnIdle( wxIdleEvent& event ) = 0;
					virtual void OnToggleBottomPanel( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnToggleLog( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnToggleFullscreen( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnViewModules( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnLoadModule( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnUnloadModule( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnSceneCreate( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnSceneDelete( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnNodeCreate( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnNodeDelete( wxRibbonToolBarEvent& event ) = 0;
					virtual void OnSceneChanged( wxCommandEvent& event ) = 0;
					virtual void OnSize( wxSizeEvent& event ) = 0;
					
				
				public:
					
					EditorMainWindowBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Punk Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1024,840 ), long style = wxDEFAULT_FRAME_STYLE|wxMAXIMIZE|wxTAB_TRAVERSAL );
					
					~EditorMainWindowBase();
				
			};
			
			///////////////////////////////////////////////////////////////////////////////
			/// Class CreateSceneDialog
			///////////////////////////////////////////////////////////////////////////////
			class CreateSceneDialog : public wxDialog 
			{
				private:
				
				protected:
					wxTextCtrl* m_scene_name;
					wxButton* m_ok;
					wxButton* m_cancel;
					
					// Virtual event handlers, overide them in your derived class
					virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
					virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }
					
				
				public:
					
					CreateSceneDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Create scene"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
					~CreateSceneDialog();
				
			};
			
		} // namespace Tools
	} // namespace Engine
} // namespace Punk

#endif //__FORMS_H__
